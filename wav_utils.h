#ifndef WAV_UTILS_H
    #define WAV_UTILS_H

    #include <alsa/asoundlib.h>
    #include <alsa/pcm.h>

    #include "errors.h"
    #include "utils.h"

    #define ID_DATA_CHUNK   "data"
    #define WAV_OFFSET      12
    #define WAV_PCM_FORMAT  1
    #define BITS_PER_BYTE   8

    #define S8_BIT          8
    #define S16_BIT         16
    #define S24_BIT         24

    #define STR_CHUNK_SIZE          "\tChunk size: "
    #define STR_AUDIO_FORMAT        "\tAudio format: "
    #define STR_NUMBER_OF_CHANNELS  "\tNumber of channels: "
    #define STR_SUBCHUNK_SIZE       "\tSubchunk size: "
    #define STR_SAMPLE_RATE         "\tSample rate: "
    #define STR_BYTE_RATE           "\tByte rate: "
    #define STR_BLOCK_ALIGN         "\tBlock align: "
    #define STR_BITS_PER_SAMPLE     "\tBits per sample: "     

    /* Assumes a little endian platform */
    typedef struct {
        /* Header of a WAV file */
        char chunkID[4];
        int  chunkSize;
        char format[4];
    } wav_header_t;

    typedef struct {
        char formatChunkID[4];
        int  formatChunkSize;
        short int audioFormat;
        short int numChannels;
        int sampleRate;
        int byteRate;
        short int blockAlign;
        short int bitsPerSample;
    } wav_format_t;

    typedef struct {
        char ID[4];
        int size;
    } subchunk_info_t;

    bool_t is_data_chunk(const subchunk_info_t *chunk);
    status_t print_ID(const char *id);
    status_t print_header_info(const wav_header_t *header, const wav_format_t *format);
    status_t get_wav_data(FILE *wav_file, void **song_data, subchunk_info_t *chunk);
    status_t get_header_data(FILE *wav_file, wav_header_t *header, wav_format_t *format);
    status_t get_pcm_format(const wav_format_t *format, snd_pcm_format_t *pcm_format);
#endif