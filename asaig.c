/* Minimal (like extermely minimal) wav player for ALSA
 * Author: Bocchio
 * */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <alsa/asoundlib.h>
#include <alsa/pcm.h>

#include "errors.h"
#include "utils.h"
#include "wav_utils.h"

#define LATENCY         500000
#define SOFT_RESAMPLE   1 /* Allow resampling */
#define DEVICE          "default"

#define CMD_ARGS_LEN                2
#define CMD_SONG_FILE_ARG           1

snd_output_t *output = NULL;

status_t validate_parameters(int, char **, char **);

int main(int argc, char *argv[])
{
    int state;

    snd_pcm_t *handle;
    snd_pcm_format_t pcm_format;

    char *path;
    FILE *song_file;
    wav_header_t header;
    wav_format_t format;
    subchunk_info_t data_chunk_info;
    void *song_data;

    if((state = validate_parameters(argc, argv, &path)) != SUCCESS){
        show_error(state);
        return state;
    }

    if((song_file = fopen(path, "rb")) == NULL){
        state = ERROR_OPENING_FILE;
        show_error_info(state, path);
        return state;
    }

    if((state = get_header_data(song_file, &header, &format)) != SUCCESS){
        show_error_info(state, path);
        return state;
    }

    /* get the audio data from the file */
    if((state = get_wav_data(song_file, &song_data, &data_chunk_info)) != SUCCESS){
        show_error_info(state, path);
        return state;
    }

    /* get the proper ALSA pcm format for that file */
    if((state = get_pcm_format(&format, &pcm_format)) != SUCCESS){
        show_error(state);
        return state;
    }

    /* print header data because, why not? */ 
    print_header_info(&header, &format);

    /* open the pcm device */
    if((state = snd_pcm_open(&handle, DEVICE, SND_PCM_STREAM_PLAYBACK, 0)) != SUCCESS) {
            fprintf(stderr, "%s\n", snd_strerror(state));
            state = ERROR_OPENING_DEVICE;
            show_error_info(state, DEVICE);
            return state;
    }

    /* config the pcm device with all the parameters in the file */
    if ((state = snd_pcm_set_params(handle,
                                    pcm_format,
                                    SND_PCM_ACCESS_RW_INTERLEAVED,
                                    format.numChannels,
                                    format.sampleRate,
                                    SOFT_RESAMPLE,
                                    LATENCY)) != SUCCESS) {   
            fprintf(stderr, "%s\n", snd_strerror(state));
            state = ERROR_CONFIG_DEVICE;
            show_error_info(state, DEVICE);
            return state;
    }

    /* play the song */
    snd_pcm_writei(handle, song_data, BITS_PER_BYTE*data_chunk_info.size/format.bitsPerSample);

    snd_pcm_close(handle);
    fclose(song_file);

    return SUCCESS;
}

status_t validate_parameters(int argc, char **argv, char **file_path)
{
    if(file_path == NULL)
        return ERROR_NULL_POINTER;
    
    if(argc !=  CMD_ARGS_LEN)
        return ERROR_CMD_LINE_ARGS;

    if((*file_path = malloc(strlen(argv[CMD_SONG_FILE_ARG])+1)) == NULL)
        return ERROR_MEMORY;

    strcpy(*file_path, argv[CMD_SONG_FILE_ARG]);

    return SUCCESS;
}