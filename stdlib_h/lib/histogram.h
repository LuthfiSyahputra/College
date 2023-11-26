#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "output.h"
#include "datatype.h"


#define MAX_HISTOGRAM_LEN   32

// int horHistogram(const char* varName[], void* data, int nData, int barLen, int datatype);

int _printBar();
size_t highest(void* data, int n, int sizeof_data, int (*_cmpfunc)(void*, void*));


size_t _highest_size_t(void* _baseptr, int n, int datatype);
type_t _highest_type_T(void* data, int n, int datatype);

int horHistogram(const char* varName[], void* data, int nData, size_t barLen, int datatype);

int horHistogram(const char* varName[], void* data, int nData, size_t barLen, int datatype) {
    
    // search the highest data
    type_t highest = { 0 };
    ptr_t  pdata = { data };
    for (int i = 0; i < nData; i++) {
        switch (datatype)
        {
        case TYPE_8: case TYPE_8U:
            if(*pdata.uint8 > highest.uint8)   highest.uint8 = *pdata.uint8;
            pdata.uint8++;  break;
        case TYPE_16: case TYPE_16U:
            if(*pdata.uint16 > highest.uint16) highest.uint16 = *pdata.uint16;
            pdata.uint16++; break;
        case TYPE_32: case TYPE_32U:
            if(*pdata.uint32 > highest.uint32) highest.uint32 = *pdata.uint32;
            pdata.uint32++; break;
        case TYPE_64: case TYPE_64U:
            if(*pdata.uint64 > highest.uint64) highest.uint64 = *pdata.uint64;
            pdata.uint64++; break;

        case TYPE_F:
            if(*pdata.f > highest.f) highest.f = *pdata.f;
            pdata.f++; break;
        case TYPE_LF:
            if(*pdata.lf > highest.lf) highest.lf = *pdata.lf;
            pdata.lf++; break;
        
        default:
            return -1;
        }
    }


    // print the histogram
    pdata.base = data;
    int _barlen;
    for (size_t i = 0; i < nData; i++) {
        switch (datatype)
        {
        case TYPE_8: case TYPE_8U:
            _barlen = ((*pdata.uint8++ * barLen) / highest.uint8);
            break;
        case TYPE_16: case TYPE_16U:
            _barlen = ((*pdata.uint16++ * barLen) / highest.uint16);
            break;
        case TYPE_32: case TYPE_32U:
#if         __SIZEOF_SIZE_T__ != 8
            _barlen = normalize(*pdata.uint32++, highest.uint32) * barLen;
#else
            _barlen = ((*pdata.uint32++ * barLen) / highest.uint32);
#endif
            break;
        case TYPE_64: case TYPE_64U:
            _barlen = normalize(*pdata.uint64++, highest.uint64) * barLen;
            break;

        case TYPE_F:
            _barlen = ((*pdata.f++ / highest.f) * barLen);
            break;
        case TYPE_LF:
            _barlen = ((*pdata.lf++ / highest.lf) * barLen);
            break;
        default:
            break;
        }

        printf("barlen: %4d  actual: {%4d | %4d}  highest: %llu\n", barLen, _barlen, barLen - _barlen, highest.uint64);
        // fprintf(stdout, "%c | %s%s\n", (i + 'A'),cloneCh_c('>', _barlen), cloneCh_c(' ', barLen - _barlen));
    }
    
    
}

size_t _highest_size_t(void* _baseptr, int n, int datatype){
    // register type_t highest = { 0 };
    register byte* data = _baseptr;
    register size_t highest_t = { 0 };
    register size_t tempval = { 0 };

    for (int i = 0; i < n; i++) {
        switch (datatype)
        {
        case TYPE_8: case TYPE_8U:
            tempval = *(uint8_t*) data;
            data += sizeof(uint8_t);
            break;
        case TYPE_16: case TYPE_16U:
            tempval = *(uint16_t*) data;
            data += sizeof(uint16_t);
            break;
        case TYPE_32: case TYPE_32U:
            tempval = *(uint32_t*) data;
            data += sizeof(uint32_t);
            break;
        case TYPE_64: case TYPE_64U:
            tempval = *(uint64_t*) data;
            data += sizeof(uint64_t);
            break;

        case TYPE_F:
            tempval = *(float*) data;
            data += sizeof(float);
            break;
        case TYPE_LF:
            tempval = *(double*) data;
            data += sizeof(double);
            break;
        
        default:
            return 0;
        }

        if(tempval > highest_t) highest_t = tempval;
    }

    return highest_t;
}

type_t _highest_type_T(void* data, int n, int datatype){
    register type_t highest = { 0 };
    // register size_t highest_t = { 0 };
    register size_t tempval = { 0 };
    register ptr_t pdata = { data };

    for (int i = 0; i < n; i++) {
        switch (datatype)
        {
        case TYPE_8: case TYPE_8U:
            tempval = *pdata.uint8++;
            break;
        case TYPE_16: case TYPE_16U:
            tempval = *pdata.uint16++;
            break;
        case TYPE_32: case TYPE_32U:
            tempval = *pdata.uint32++;
            break;
        case TYPE_64: case TYPE_64U:
            tempval = *pdata.uint64++;
            break;

        case TYPE_F:
            tempval = *pdata.f++;
            break;
        case TYPE_LF:
            tempval = *pdata.lf++;
            break;
        
        default:
            return (type_t) 0;
        }

        if(tempval > highest.base) highest.base = tempval;
    }

    return highest;

}

#endif