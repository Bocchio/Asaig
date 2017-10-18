#include "wav_utils.h"

bool_t is_data_chunk(const subchunk_info_t *chunk)
{
    size_t i;
    for(i = 0; i < strlen(ID_DATA_CHUNK); i++)
        if(chunk->ID[i] != ID_DATA_CHUNK[i])
            return FALSE;
    return TRUE;
}

status_t print_ID(const char *id)
{
    if(id == NULL)
        return ERROR_NULL_POINTER;
    printf("%c%c%c%c\n", id[0],
                         id[1],
                         id[2],
                         id[3]);
    return SUCCESS;
}

status_t print_header_info(const wav_header_t *header, const wav_format_t *format)
{
    if(header == NULL)
        return ERROR_NULL_POINTER;

    print_ID(header->chunkID);
    printf("%s%d\n", STR_CHUNK_SIZE, header->chunkSize);
    print_ID(header->format);

    print_ID(format->formatChunkID);
    printf("%s%d\n"
           "%s%d\n"
           "%s%d\n"
           "%s%d\n"
           "%s%d\n"
           "%s%d\n"
           "%s%d\n",
           STR_SUBCHUNK_SIZE, format->formatChunkSize,
           STR_AUDIO_FORMAT, format->audioFormat,
           STR_NUMBER_OF_CHANNELS, format->numChannels,
           STR_SAMPLE_RATE, format->sampleRate,
           STR_BYTE_RATE, format->byteRate,
           STR_BLOCK_ALIGN, format->blockAlign,
           STR_BITS_PER_SAMPLE, format->bitsPerSample);

    return SUCCESS;
}

status_t get_header_data(FILE *wav_file, wav_header_t *header, wav_format_t *format)
{
    if(header == NULL || format == NULL)
        return ERROR_NULL_POINTER;

    if(!fread(header, sizeof(wav_header_t), 1, wav_file))
        return ERROR_READING_FILE;

    if(!fread(format, sizeof(wav_format_t), 1, wav_file))
        return ERROR_READING_FILE;

    return SUCCESS;
}

status_t get_wav_data(FILE *wav_file, void **song_data, subchunk_info_t *chunk)
{
    memset(chunk, 0, sizeof(*chunk));

    fseek(wav_file, WAV_OFFSET, SEEK_SET);
    
    while(!is_data_chunk(chunk)){
        fseek(wav_file, chunk->size, SEEK_CUR);
        if(!fread(chunk, sizeof(chunk), 1, wav_file))
            return ERROR_READING_FILE;
    }

    if((*song_data = malloc(chunk->size)) == NULL)
        return ERROR_MEMORY;

    if(!fread(*song_data, chunk->size, 1, wav_file))
        return ERROR_READING_FILE;

    return SUCCESS;
}

status_t get_pcm_format(const wav_format_t *format, snd_pcm_format_t *pcm_format)
{
    if(format == NULL || pcm_format == NULL)
        return ERROR_NULL_POINTER;

    if(format->audioFormat != WAV_PCM_FORMAT)
        return ERROR_INVALID_FILE;

    switch(format->bitsPerSample){
        case S8_BIT:
            *pcm_format = SND_PCM_FORMAT_S8;
            break;
        case S16_BIT:
            *pcm_format = SND_PCM_FORMAT_S16_LE;
            break;
        case S24_BIT:
            *pcm_format = SND_PCM_FORMAT_S24_LE;
            break;
        default:
            return ERROR_INVALID_FILE;
    }

    return SUCCESS;
}