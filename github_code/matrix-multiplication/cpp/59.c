#include "ncrx.h"

extern sockaddr_in addr(unsigned int ip, unsigned short int port);

#define UNROLL_MATRIX_MULTIPLICATION_2(session, output, position, row_index, accumulator) \
accumulator   = FiniteField::instance()->mul(session->_decoding_matrix[row_index].decode[0], session->_buffer[0].pkt.buffer[position]),\
accumulator ^= FiniteField::instance()->mul(session->_decoding_matrix[row_index].decode[1], session->_buffer[1].pkt.buffer[position]),\
output[position] = accumulator

#define UNROLL_MATRIX_MULTIPLICATION_4(session, output, position, row_index, accumulator) \
accumulator   = FiniteField::instance()->mul(session->_decoding_matrix[row_index].decode[0], session->_buffer[0].pkt.buffer[position]),\
accumulator ^= FiniteField::instance()->mul(session->_decoding_matrix[row_index].decode[1], session->_buffer[1].pkt.buffer[position]),\
accumulator ^= FiniteField::instance()->mul(session->_decoding_matrix[row_index].decode[2], session->_buffer[2].pkt.buffer[position]),\
accumulator ^= FiniteField::instance()->mul(session->_decoding_matrix[row_index].decode[3], session->_buffer[3].pkt.buffer[position]),\
output[position] = accumulator

#define UNROLL_MATRIX_MULTIPLICATION_8(session, output, position, row_index, accumulator) \
accumulator   = FiniteField::instance()->mul(session->_decoding_matrix[row_index].decode[0], session->_buffer[0].pkt.buffer[position]),\
accumulator ^= FiniteField::instance()->mul(session->_decoding_matrix[row_index].decode[1], session->_buffer[1].pkt.buffer[position]),\
accumulator ^= FiniteField::instance()->mul(session->_decoding_matrix[row_index].decode[2], session->_buffer[2].pkt.buffer[position]),\
accumulator ^= FiniteField::instance()->mul(session->_decoding_matrix[row_index].decode[3], session->_buffer[3].pkt.buffer[position]),\
accumulator ^= FiniteField::instance()->mul(session->_decoding_matrix[row_index].decode[4], session->_buffer[4].pkt.buffer[position]),\
accumulator ^= FiniteField::instance()->mul(session->_decoding_matrix[row_index].decode[5], session->_buffer[5].pkt.buffer[position]),\
accumulator ^= FiniteField::instance()->mul(session->_decoding_matrix[row_index].decode[6], session->_buffer[6].pkt.buffer[position]),\
accumulator ^= FiniteField::instance()->mul(session->_decoding_matrix[row_index].decode[7], session->_buffer[7].pkt.buffer[position]),\
output[position] = accumulator

#define UNROLL_MATRIX_MULTIPLICATION_16(session, output, position, row_index, accumulator) \
accumulator   = FiniteField::instance()->mul(session->_decoding_matrix[row_index].decode[0], session->_buffer[0].pkt.buffer[position]),\
accumulator ^= FiniteField::instance()->mul(session->_decoding_matrix[row_index].decode[1], session->_buffer[1].pkt.buffer[position]),\
accumulator ^= FiniteField::instance()->mul(session->_decoding_matrix[row_index].decode[2], session->_buffer[2].pkt.buffer[position]),\
accumulator ^= FiniteField::instance()->mul(session->_decoding_matrix[row_index].decode[3], session->_buffer[3].pkt.buffer[position]),\
accumulator ^= FiniteField::instance()->mul(session->_decoding_matrix[row_index].decode[4], session->_buffer[4].pkt.buffer[position]),\
accumulator ^= FiniteField::instance()->mul(session->_decoding_matrix[row_index].decode[5], session->_buffer[5].pkt.buffer[position]),\
accumulator ^= FiniteField::instance()->mul(session->_decoding_matrix[row_index].decode[6], session->_buffer[6].pkt.buffer[position]),\
accumulator ^= FiniteField::instance()->mul(session->_decoding_matrix[row_index].decode[7], session->_buffer[7].pkt.buffer[position]),\
accumulator ^= FiniteField::instance()->mul(session->_decoding_matrix[row_index].decode[8], session->_buffer[8].pkt.buffer[position]),\
accumulator ^= FiniteField::instance()->mul(session->_decoding_matrix[row_index].decode[9], session->_buffer[9].pkt.buffer[position]),\
accumulator ^= FiniteField::instance()->mul(session->_decoding_matrix[row_index].decode[10], session->_buffer[10].pkt.buffer[position]),\
accumulator ^= FiniteField::instance()->mul(session->_decoding_matrix[row_index].decode[11], session->_buffer[11].pkt.buffer[position]),\
accumulator ^= FiniteField::instance()->mul(session->_decoding_matrix[row_index].decode[12], session->_buffer[12].pkt.buffer[position]),\
accumulator ^= FiniteField::instance()->mul(session->_decoding_matrix[row_index].decode[13], session->_buffer[13].pkt.buffer[position]),\
accumulator ^= FiniteField::instance()->mul(session->_decoding_matrix[row_index].decode[14], session->_buffer[14].pkt.buffer[position]),\
accumulator ^= FiniteField::instance()->mul(session->_decoding_matrix[row_index].decode[15], session->_buffer[15].pkt.buffer[position]),\
output[position] = accumulator

rx_session_info::rx_session_info(sockaddr_in addr, unsigned char blk_size): _ADDR(addr),_MAX_BLOCK_SIZE(blk_size)
{
    _state = rx_session_info::STATE::INIT_FAILURE;
    _rank = 0;
    try
    {
        _buffer = new PktBuffer[_MAX_BLOCK_SIZE];
        for(unsigned char i = 0 ; i < _MAX_BLOCK_SIZE ; i++)
        {
            _buffer[i].delivered = false;
            memset(_buffer[i].pkt.buffer, 0x0, sizeof(NetworkCodingPktBuffer));
        }
    }
    catch(std::exception ex)
    {
        return;
    }
    _blk_seq = 0;
    try
    {
        _decoding_matrix = new DecodingBuffer[_MAX_BLOCK_SIZE];
        for(unsigned char index = 0 ; index < _MAX_BLOCK_SIZE ; index++)
        {
            _decoding_matrix[index].empty = true;
            _decoding_matrix[index].encode = nullptr;
            _decoding_matrix[index].decode = nullptr;
        }
    }
    catch(std::exception &ex)
    {
        delete [] _buffer;
        _buffer = nullptr;
        return;
    }
    try
    {
        for(unsigned char index = 0 ; index < _MAX_BLOCK_SIZE ; index++)
        {
            _decoding_matrix[index].encode = new unsigned char[_MAX_BLOCK_SIZE];
            memset(_decoding_matrix[index].encode, 0x0, _MAX_BLOCK_SIZE);
            _decoding_matrix[index].decode = new unsigned char[_MAX_BLOCK_SIZE];
            memset(_decoding_matrix[index].decode, 0x0, _MAX_BLOCK_SIZE);
        }
    }
    catch(std::exception ex)
    {
        for(unsigned char index = 0 ; index < _MAX_BLOCK_SIZE ; index++)
        {
            if(_decoding_matrix[index].encode != nullptr)
            {
                delete [] _decoding_matrix[index].encode;
            }
            if(_decoding_matrix[index].decode != nullptr)
            {
                delete [] _decoding_matrix[index].decode;
            }
        }
        delete [] _decoding_matrix;
        _decoding_matrix = nullptr;
        delete [] _buffer;
        _buffer = nullptr;
    }
    _losses = 0;
    _state = rx_session_info::STATE::INIT_SUCCESS;
}

rx_session_info::~rx_session_info()
{
    if(_state == rx_session_info::STATE::INIT_FAILURE)
    {
        return;
    }
    for(unsigned char index = 0 ; index < _MAX_BLOCK_SIZE ; index++)
    {
        if(_decoding_matrix[index].encode != nullptr)
        {
            delete [] _decoding_matrix[index].encode;
        }
        if(_decoding_matrix[index].decode != nullptr)
        {
            delete [] _decoding_matrix[index].decode;
        }
    }
    delete [] _decoding_matrix;
    _decoding_matrix = nullptr;
    delete [] _buffer;
    _buffer = nullptr;
}

bool ncrx::_handle_original_packet(rx_session_info* const session_info, const unsigned char * const pkt, int size)
{
    // Copy original packet to the relavant position in _buffer.
    // For original pkt, GET_OUTER_BLK_SIZE(pkt) is _tx_cnt.

    const unsigned short int index = GET_OUTER_BLK_SIZE(pkt);
    if(session_info->_buffer[index].delivered == true)
    {
        if(index != 0)
        {
            std::cout<<"Something is wrong!!!!["<<0+index<<"]\n";
            exit(-1);
        }
        return (session_info->_rank == GET_OUTER_BLK_SIZE(pkt)) && (GET_OUTER_FLAGS(session_info->_buffer[index].pkt.buffer) & OuterHeader::FLAGS_END_OF_BLK);
    }
    session_info->_buffer[index].delivered = false;
    memcpy(session_info->_buffer[index].pkt.buffer, pkt, GET_OUTER_SIZE(pkt));
    session_info->_decoding_matrix[index].empty = false;
    memcpy(session_info->_decoding_matrix[index].encode, GET_INNER_CODE(pkt), session_info->_MAX_BLOCK_SIZE);
    memcpy(session_info->_decoding_matrix[index].decode, GET_INNER_CODE(pkt), session_info->_MAX_BLOCK_SIZE);
    bool send_ack = false;
    if(session_info->_rank == GET_OUTER_BLK_SIZE(pkt))
    {
        if(_receive_callback != nullptr)
        {
            _receive_callback(GET_INNER_PAYLOAD(session_info->_buffer[index].pkt.buffer, session_info->_MAX_BLOCK_SIZE), GET_INNER_SIZE(session_info->_buffer[index].pkt.buffer), session_info->_ADDR);
            session_info->_buffer[index].delivered = true; // The packet is delivered.
        }
        // All original packets in the block are received without losses.
        // Send the ack.
        if(GET_OUTER_FLAGS(session_info->_buffer[index].pkt.buffer) & OuterHeader::FLAGS_END_OF_BLK)
        {
            send_ack = true;
        }
    }
    session_info->_rank++;
    return send_ack;
}

int ncrx::_innovative(rx_session_info * const session_info, unsigned char* pkt)
{
    // 1. find an empty slot.
    int innovative_index = 0;
    for( ; innovative_index < session_info->_MAX_BLOCK_SIZE ; innovative_index++)
    {
        if(session_info->_decoding_matrix[innovative_index].empty == true)
        {
            session_info->_decoding_matrix[innovative_index].empty = false;
            memcpy(session_info->_decoding_matrix[innovative_index].encode, GET_INNER_CODE(pkt), session_info->_MAX_BLOCK_SIZE);
            memset(session_info->_decoding_matrix[innovative_index].decode, 0x0, session_info->_MAX_BLOCK_SIZE);
            session_info->_decoding_matrix[innovative_index].decode[innovative_index] = 1;
            break;
        }
    }
    if(innovative_index >= session_info->_MAX_BLOCK_SIZE)
    {
        return -1;
    }

    // 2. eliminate redundunt information of pkt
    for(unsigned char buffer_index = 0 ; buffer_index < session_info->_MAX_BLOCK_SIZE ; buffer_index++)
    {
        if(session_info->_decoding_matrix[buffer_index].empty == true)
        {
            continue;
        }
        if(session_info->_decoding_matrix[innovative_index].encode[buffer_index] == 0)
        {
            continue;
        }
        if(buffer_index == innovative_index)
        {
            continue;
        }
        const unsigned char mul = session_info->_decoding_matrix[innovative_index].encode[buffer_index];
        for(unsigned char code_index = 0 ; code_index < session_info->_MAX_BLOCK_SIZE ; code_index++)
        {
            session_info->_decoding_matrix[innovative_index].encode[code_index] = FiniteField::instance()->mul(session_info->_decoding_matrix[buffer_index].encode[code_index], mul) ^ session_info->_decoding_matrix[innovative_index].encode[code_index];
            session_info->_decoding_matrix[innovative_index].decode[code_index] = FiniteField::instance()->mul(session_info->_decoding_matrix[buffer_index].decode[code_index], mul) ^ session_info->_decoding_matrix[innovative_index].decode[code_index];
        }
    }

    // 3. check innovativity
    if(session_info->_decoding_matrix[innovative_index].encode[innovative_index] == 0)
    {
        session_info->_decoding_matrix[innovative_index].empty = true;
        memset(session_info->_decoding_matrix[innovative_index].encode, 0x0, session_info->_MAX_BLOCK_SIZE);
        memset(session_info->_decoding_matrix[innovative_index].decode, 0x0, session_info->_MAX_BLOCK_SIZE);
        return -1;
    }

    // 4. Make _decoding_matrix[innovative_index].encode[innovative_index] to be 1.
    if(session_info->_decoding_matrix[innovative_index].encode[innovative_index] != 1)
    {
        const unsigned char mul = FiniteField::instance()->inv(session_info->_decoding_matrix[innovative_index].encode[innovative_index]);
        for(unsigned char code_index = 0 ; code_index < session_info->_MAX_BLOCK_SIZE ; code_index++)
        {
            session_info->_decoding_matrix[innovative_index].encode[code_index] = FiniteField::instance()->mul(session_info->_decoding_matrix[innovative_index].encode[code_index], mul);
            session_info->_decoding_matrix[innovative_index].decode[code_index] = FiniteField::instance()->mul(session_info->_decoding_matrix[innovative_index].decode[code_index], mul);
        }
    }

    // 5. remove redundunt information from the buffer
    for(unsigned char buffer_index = 0 ; buffer_index < session_info->_MAX_BLOCK_SIZE ; buffer_index++)
    {
        if(session_info->_decoding_matrix[buffer_index].empty == true)
        {
            continue;
        }
        if(session_info->_decoding_matrix[buffer_index].encode[innovative_index] == 0)
        {
            continue;
        }
        if(buffer_index == innovative_index)
        {
            continue;
        }
        const unsigned char mul = session_info->_decoding_matrix[buffer_index].encode[innovative_index];
        for(unsigned char code_index = 0 ; code_index < session_info->_MAX_BLOCK_SIZE ; code_index++)
        {
            session_info->_decoding_matrix[buffer_index].encode[code_index] = FiniteField::instance()->mul( session_info->_decoding_matrix[innovative_index].encode[code_index], mul ) ^ \
                    session_info->_decoding_matrix[buffer_index].encode[code_index];
            session_info->_decoding_matrix[buffer_index].decode[code_index] = FiniteField::instance()->mul( session_info->_decoding_matrix[innovative_index].decode[code_index], mul ) ^ \
                    session_info->_decoding_matrix[buffer_index].decode[code_index];
        }
    }

    return innovative_index;
}

void ncrx::_decode(rx_session_info * const session_info, unsigned char* pkt, int size)
{
    int innovative_index = _innovative(session_info, pkt);
    if(innovative_index == -1)
    {
        return;
    }
    session_info->_buffer[innovative_index].delivered = false;
    memcpy(session_info->_buffer[innovative_index].pkt.buffer, pkt, GET_OUTER_SIZE(pkt));
    session_info->_rank++;
    session_info->_losses++;
}

bool ncrx::_handle_remedy_packet(rx_session_info* const session_info, unsigned char *pkt, int size)
{
    if(session_info->_rank == GET_OUTER_BLK_SIZE(pkt)+1)
    {
        return true;
    }
    _decode(session_info, pkt, size);
    if(session_info->_rank == GET_OUTER_BLK_SIZE(pkt)+1)
    {
        for(unsigned char i = 0 ; i < session_info->_rank ; i++)
        {
            if(session_info->_buffer[i].delivered == false)
            {
                if((GET_OUTER_FLAGS(session_info->_buffer[i].pkt.buffer) & OuterHeader::FLAGS_ORIGINAL) == 0)
                {
                    memcpy(session_info->_decoding_buffer.buffer, session_info->_buffer[i].pkt.buffer, OUTER_HEADER_SIZE);
                    // decoding
                    for(unsigned int decoding_position = OUTER_HEADER_SIZE ; decoding_position < GET_OUTER_SIZE(session_info->_buffer[i].pkt.buffer) ; )
                    {
                        if(GET_OUTER_SIZE(session_info->_buffer[i].pkt.buffer) - decoding_position > 1023)
                        {
                            _unroll_decode_1024(session_info, session_info->_decoding_buffer.buffer, decoding_position, i);
                            decoding_position+=1024;
                        }
                        else if(GET_OUTER_SIZE(session_info->_buffer[i].pkt.buffer) - decoding_position > 511)
                        {
                            _unroll_decode_512(session_info, session_info->_decoding_buffer.buffer, decoding_position, i);
                            decoding_position+=512;
                        }
                        else if(GET_OUTER_SIZE(session_info->_buffer[i].pkt.buffer) - decoding_position > 255)
                        {
                            _unroll_decode_256(session_info, session_info->_decoding_buffer.buffer, decoding_position, i);
                            decoding_position+=256;
                        }
                        else if(GET_OUTER_SIZE(session_info->_buffer[i].pkt.buffer) - decoding_position > 127)
                        {
                            _unroll_decode_128(session_info, session_info->_decoding_buffer.buffer, decoding_position, i);
                            decoding_position+=128;
                        }
                        else if(GET_OUTER_SIZE(session_info->_buffer[i].pkt.buffer) - decoding_position > 63)
                        {
                            _unroll_decode_64(session_info, session_info->_decoding_buffer.buffer, decoding_position, i);
                            decoding_position+=64;
                        }
                        else if(GET_OUTER_SIZE(session_info->_buffer[i].pkt.buffer) - decoding_position > 31)
                        {
                            _unroll_decode_32(session_info, session_info->_decoding_buffer.buffer, decoding_position, i);
                            decoding_position+=32;
                        }
                        else if(GET_OUTER_SIZE(session_info->_buffer[i].pkt.buffer) - decoding_position > 15)
                        {
                            _unroll_decode_16(session_info, session_info->_decoding_buffer.buffer, decoding_position, i);
                            decoding_position+=16;
                        }
                        else if(GET_OUTER_SIZE(session_info->_buffer[i].pkt.buffer) - decoding_position > 7)
                        {
                            _unroll_decode_8(session_info, session_info->_decoding_buffer.buffer, decoding_position, i);
                            decoding_position+=8;
                        }
                        else if(GET_OUTER_SIZE(session_info->_buffer[i].pkt.buffer) - decoding_position > 3)
                        {
                            _unroll_decode_4(session_info, session_info->_decoding_buffer.buffer, decoding_position, i);
                            decoding_position+=4;
                        }
                        else if(GET_OUTER_SIZE(session_info->_buffer[i].pkt.buffer) - decoding_position > 1)
                        {
                            _unroll_decode_2(session_info, session_info->_decoding_buffer.buffer, decoding_position, i);
                            decoding_position+=2;
                        }
                        else if(GET_OUTER_SIZE(session_info->_buffer[i].pkt.buffer) - decoding_position > 0)
                        {
                            unsigned char accumulator;
                            switch(session_info->_MAX_BLOCK_SIZE)
                            {
                            case 2:
                                UNROLL_MATRIX_MULTIPLICATION_2(session_info, session_info->_decoding_buffer.buffer, decoding_position, i, accumulator);
                                break;
                            case 4:
                                UNROLL_MATRIX_MULTIPLICATION_4(session_info, session_info->_decoding_buffer.buffer, decoding_position, i, accumulator);
                                break;
                            case 8:
                                UNROLL_MATRIX_MULTIPLICATION_8(session_info, session_info->_decoding_buffer.buffer, decoding_position, i, accumulator);
                                break;
                            case 16:
                                UNROLL_MATRIX_MULTIPLICATION_16(session_info, session_info->_decoding_buffer.buffer, decoding_position, i, accumulator);
                                break;
                            }
                            decoding_position+=1;
                        }
                    }
                    if(_receive_callback != nullptr)
                    {
                        _receive_callback(GET_INNER_PAYLOAD(session_info->_decoding_buffer.buffer, session_info->_MAX_BLOCK_SIZE), GET_INNER_SIZE(session_info->_decoding_buffer.buffer), session_info->_ADDR);
                        session_info->_buffer[i].delivered = true; // The packet is delivered.
                    }
                }
                else
                {
                    if(_receive_callback != nullptr)
                    {
                        _receive_callback(GET_INNER_PAYLOAD(session_info->_buffer[i].pkt.buffer, session_info->_MAX_BLOCK_SIZE), GET_INNER_SIZE(session_info->_buffer[i].pkt.buffer), session_info->_ADDR);
                        session_info->_buffer[i].delivered = true; // The packet is delivered.
                    }
                }
            }
        }

        return true;
    }
    return false;
}

void ncrx::_unroll_decode_2(rx_session_info * const session_info, unsigned char *output, unsigned short position, unsigned char row_index)
{
    unsigned char accumulator;
    switch(session_info->_MAX_BLOCK_SIZE)
    {
    case 2:
        UNROLL_MATRIX_MULTIPLICATION_2(session_info, output, position, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_2(session_info, output, position+1, row_index, accumulator);
        break;
    case 4:
        UNROLL_MATRIX_MULTIPLICATION_4(session_info, output, position, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_4(session_info, output, position+1, row_index, accumulator);
        break;
    case 8:
        UNROLL_MATRIX_MULTIPLICATION_8(session_info, output, position, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_8(session_info, output, position+1, row_index, accumulator);
        break;
    case 16:
        UNROLL_MATRIX_MULTIPLICATION_16(session_info, output, position, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_16(session_info, output, position+1, row_index, accumulator);
        break;
    }
}

void ncrx::_unroll_decode_4(rx_session_info * const session_info, unsigned char *output, unsigned short position, unsigned char row_index)
{
    unsigned char accumulator;
    switch(session_info->_MAX_BLOCK_SIZE)
    {
    case 2:
        UNROLL_MATRIX_MULTIPLICATION_2(session_info, output, position, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_2(session_info, output, position+1, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_2(session_info, output, position+2, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_2(session_info, output, position+3, row_index, accumulator);
        break;
    case 4:
        UNROLL_MATRIX_MULTIPLICATION_4(session_info, output, position, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_4(session_info, output, position+1, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_4(session_info, output, position+2, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_4(session_info, output, position+3, row_index, accumulator);
        break;
    case 8:
        UNROLL_MATRIX_MULTIPLICATION_8(session_info, output, position, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_8(session_info, output, position+1, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_8(session_info, output, position+2, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_8(session_info, output, position+3, row_index, accumulator);
        break;
    case 16:
        UNROLL_MATRIX_MULTIPLICATION_16(session_info, output, position, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_16(session_info, output, position+1, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_16(session_info, output, position+2, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_16(session_info, output, position+3, row_index, accumulator);
        break;
    }
}

void ncrx::_unroll_decode_8(rx_session_info * const session_info, unsigned char *output, unsigned short position, unsigned char row_index)
{
    unsigned char accumulator;
    switch(session_info->_MAX_BLOCK_SIZE)
    {
    case 2:
        UNROLL_MATRIX_MULTIPLICATION_2(session_info, output, position, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_2(session_info, output, position+1, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_2(session_info, output, position+2, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_2(session_info, output, position+3, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_2(session_info, output, position+4, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_2(session_info, output, position+5, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_2(session_info, output, position+6, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_2(session_info, output, position+7, row_index, accumulator);
        break;
    case 4:
        UNROLL_MATRIX_MULTIPLICATION_4(session_info, output, position, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_4(session_info, output, position+1, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_4(session_info, output, position+2, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_4(session_info, output, position+3, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_4(session_info, output, position+4, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_4(session_info, output, position+5, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_4(session_info, output, position+6, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_4(session_info, output, position+7, row_index, accumulator);
        break;
    case 8:
        UNROLL_MATRIX_MULTIPLICATION_8(session_info, output, position, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_8(session_info, output, position+1, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_8(session_info, output, position+2, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_8(session_info, output, position+3, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_8(session_info, output, position+4, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_8(session_info, output, position+5, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_8(session_info, output, position+6, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_8(session_info, output, position+7, row_index, accumulator);
        break;
    case 16:
        UNROLL_MATRIX_MULTIPLICATION_16(session_info, output, position, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_16(session_info, output, position+1, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_16(session_info, output, position+2, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_16(session_info, output, position+3, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_16(session_info, output, position+4, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_16(session_info, output, position+5, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_16(session_info, output, position+6, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_16(session_info, output, position+7, row_index, accumulator);
        break;
    }
}

void ncrx::_unroll_decode_16(rx_session_info * const session_info, unsigned char *output, unsigned short position, unsigned char row_index)
{
    unsigned char accumulator;
    switch(session_info->_MAX_BLOCK_SIZE)
    {
    case 2:
        UNROLL_MATRIX_MULTIPLICATION_2(session_info, output, position, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_2(session_info, output, position+1, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_2(session_info, output, position+2, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_2(session_info, output, position+3, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_2(session_info, output, position+4, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_2(session_info, output, position+5, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_2(session_info, output, position+6, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_2(session_info, output, position+7, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_2(session_info, output, position+8, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_2(session_info, output, position+9, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_2(session_info, output, position+10, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_2(session_info, output, position+11, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_2(session_info, output, position+12, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_2(session_info, output, position+13, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_2(session_info, output, position+14, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_2(session_info, output, position+15, row_index, accumulator);
        break;
    case 4:
        UNROLL_MATRIX_MULTIPLICATION_4(session_info, output, position, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_4(session_info, output, position+1, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_4(session_info, output, position+2, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_4(session_info, output, position+3, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_4(session_info, output, position+4, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_4(session_info, output, position+5, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_4(session_info, output, position+6, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_4(session_info, output, position+7, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_4(session_info, output, position+8, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_4(session_info, output, position+9, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_4(session_info, output, position+10, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_4(session_info, output, position+11, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_4(session_info, output, position+12, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_4(session_info, output, position+13, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_4(session_info, output, position+14, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_4(session_info, output, position+15, row_index, accumulator);
        break;
    case 8:
        UNROLL_MATRIX_MULTIPLICATION_8(session_info, output, position, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_8(session_info, output, position+1, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_8(session_info, output, position+2, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_8(session_info, output, position+3, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_8(session_info, output, position+4, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_8(session_info, output, position+5, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_8(session_info, output, position+6, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_8(session_info, output, position+7, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_8(session_info, output, position+8, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_8(session_info, output, position+9, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_8(session_info, output, position+10, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_8(session_info, output, position+11, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_8(session_info, output, position+12, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_8(session_info, output, position+13, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_8(session_info, output, position+14, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_8(session_info, output, position+15, row_index, accumulator);
        break;
    case 16:
        UNROLL_MATRIX_MULTIPLICATION_16(session_info, output, position, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_16(session_info, output, position+1, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_16(session_info, output, position+2, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_16(session_info, output, position+3, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_16(session_info, output, position+4, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_16(session_info, output, position+5, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_16(session_info, output, position+6, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_16(session_info, output, position+7, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_16(session_info, output, position+8, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_16(session_info, output, position+9, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_16(session_info, output, position+10, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_16(session_info, output, position+11, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_16(session_info, output, position+12, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_16(session_info, output, position+13, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_16(session_info, output, position+14, row_index, accumulator);
        UNROLL_MATRIX_MULTIPLICATION_16(session_info, output, position+15, row_index, accumulator);
        break;
    }
}

void ncrx::_unroll_decode_32(rx_session_info * const session_info, unsigned char *output, unsigned short position, unsigned char row_index)
{
    _unroll_decode_16(session_info, output, position, row_index);
    _unroll_decode_16(session_info, output, position+16, row_index);
}

void ncrx::_unroll_decode_64(rx_session_info * const session_info, unsigned char *output, unsigned short position, unsigned char row_index)
{
    _unroll_decode_16(session_info, output, position, row_index);
    _unroll_decode_16(session_info, output, position+16, row_index);
    _unroll_decode_16(session_info, output, position+32, row_index);
    _unroll_decode_16(session_info, output, position+48, row_index);
}

void ncrx::_unroll_decode_128(rx_session_info * const session_info, unsigned char *output, unsigned short position, unsigned char row_index)
{
    _unroll_decode_16(session_info, output, position, row_index);
    _unroll_decode_16(session_info, output, position+16, row_index);
    _unroll_decode_16(session_info, output, position+32, row_index);
    _unroll_decode_16(session_info, output, position+48, row_index);
    _unroll_decode_16(session_info, output, position+64, row_index);
    _unroll_decode_16(session_info, output, position+80, row_index);
    _unroll_decode_16(session_info, output, position+96, row_index);
    _unroll_decode_16(session_info, output, position+112, row_index);

}

void ncrx::_unroll_decode_256(rx_session_info * const session_info, unsigned char *output, unsigned short position, unsigned char row_index)
{
    _unroll_decode_128(session_info, output, position, row_index);
    _unroll_decode_128(session_info, output, position+128, row_index);
}

void ncrx::_unroll_decode_512(rx_session_info * const session_info, unsigned char *output, unsigned short position, unsigned char row_index)
{
    _unroll_decode_128(session_info, output, position, row_index);
    _unroll_decode_128(session_info, output, position+128, row_index);
    _unroll_decode_128(session_info, output, position+256, row_index);
    _unroll_decode_128(session_info, output, position+384, row_index);
}

void ncrx::_unroll_decode_1024(rx_session_info * const session_info, unsigned char *output, unsigned short position, unsigned char row_index)
{
    _unroll_decode_512(session_info, output, position, row_index);
    _unroll_decode_512(session_info, output, position+512, row_index);
}


ncrx::ncrx(int socket, std::function<void (unsigned char *, unsigned int, sockaddr_in addr)> rx):_SOCKET(socket), _receive_callback(rx){}

ncrx::~ncrx()
{
    _server_session_info.perform_for_all_data([](rx_session_info* session){
        delete session;
        session = nullptr;
    });
    _server_session_info.clear();
}

void ncrx::_rx_handler(unsigned char* buffer, unsigned int size, sockaddr_in* sender_addr, unsigned int sender_addr_len)
{
    if(buffer[0] == NC_PKT_TYPE::DATA_TYPE)
    {
        if(rand()%8 == 0)
        {
            // For test, introduce random packet loss of 10%.
            return;
        }
        unsigned char* const _rx_buffer = buffer;

        const ip_port_key key = {sender_addr->sin_addr.s_addr, sender_addr->sin_port};
        rx_session_info** const lookup_result = _server_session_info.find(key);
        rx_session_info* session_info = nullptr;
        if(lookup_result == nullptr)
        {
            try
            {
                session_info = new rx_session_info((*sender_addr), GET_OUTER_MAX_BLK_SIZE(_rx_buffer));
            }
            catch(std::exception ex)
            {
                return;
            }
            if(session_info->_state == rx_session_info::STATE::INIT_FAILURE)
            {
                delete session_info;
                return;
            }
            _server_session_info.insert(key, session_info);
        }
        else
        {
            if((*lookup_result)->_MAX_BLOCK_SIZE != GET_OUTER_MAX_BLK_SIZE(_rx_buffer))
            {
                rx_session_info* new_session_info = nullptr;
                try
                {
                    new_session_info = new rx_session_info((*sender_addr), GET_OUTER_MAX_BLK_SIZE(_rx_buffer));
                }
                catch(std::exception ex)
                {
                    return;
                }
                if(session_info->_state == rx_session_info::STATE::INIT_FAILURE)
                {
                    delete new_session_info;
                    return;
                }
                delete (*lookup_result);
                (*lookup_result) = new_session_info;
            }
            session_info = (*lookup_result);
        }
        if(session_info->_state == rx_session_info::STATE::INIT_FAILURE){
            return;
        }
        const unsigned short int blk_seq = GET_OUTER_BLK_SEQ(_rx_buffer);
        /*
         * A change on a block sequence number indicates start of new block.
         * We need to flush rx buffers.
         */
        if(session_info->_blk_seq != blk_seq)
        {
            for(int i = 0 ; i < session_info->_MAX_BLOCK_SIZE ; i++)
            {
                if(session_info->_buffer[i].delivered == false &&
                        session_info->_decoding_matrix[i].empty == false &&
                        (GET_OUTER_FLAGS(session_info->_buffer[i].pkt.buffer) & OuterHeader::FLAGS_ORIGINAL) > 0)
                {
                    if(_receive_callback != nullptr)
                    {
                        _receive_callback(GET_INNER_PAYLOAD(session_info->_buffer[i].pkt.buffer, session_info->_MAX_BLOCK_SIZE), GET_INNER_SIZE(session_info->_buffer[i].pkt.buffer), session_info->_ADDR);
                        session_info->_buffer[i].delivered = true;
                    }
                }
            }
            session_info->_rank = 0;
            session_info->_blk_seq = blk_seq;
            session_info->_losses = 0;
            for(int i = 0 ; i < session_info->_MAX_BLOCK_SIZE ; i++)
            {
                session_info->_buffer[i].delivered = false;
                memset(session_info->_buffer[i].pkt.buffer, 0x0, TOTAL_HEADER_SIZE(session_info->_MAX_BLOCK_SIZE)+MAX_PAYLOAD_SIZE(session_info->_MAX_BLOCK_SIZE));
                session_info->_decoding_matrix[i].empty = true;
                memset(session_info->_decoding_matrix[i].encode, 0x0, session_info->_MAX_BLOCK_SIZE);
                memset(session_info->_decoding_matrix[i].decode, 0x0, session_info->_MAX_BLOCK_SIZE);
            }
        }
        bool send_ack = false;
        if(GET_OUTER_FLAGS(_rx_buffer) & OuterHeader::FLAGS_ORIGINAL)
        {
            send_ack = _handle_original_packet(session_info, _rx_buffer, size);
        }
        else
        {
            send_ack = _handle_remedy_packet(session_info, _rx_buffer, size);
        }
        if(send_ack)
        {
            Ack ack_pkt;
            ack_pkt.type = NC_PKT_TYPE::ACK_TYPE;
            ack_pkt.blk_seq = session_info->_blk_seq;
            ack_pkt.losses = session_info->_losses;
            if(sizeof(Ack) != sendto(_SOCKET, (void*)&ack_pkt, sizeof(Ack), 0, (sockaddr*)sender_addr, sender_addr_len))
            {
                std::cout<<"Could not send ack\n";
            }
            else
            {
                //printf("Send Ack %hu\n", ack_pkt.blk_seq);
            }
        }
    }
    else if(buffer[0] == NC_PKT_TYPE::REQ_CONNECT_TYPE)
    {
        Connect connect;
        connect.type = NC_PKT_TYPE::REP_CONNECT_TYPE;
        if(sizeof(Connect) != sendto(_SOCKET, (void*)&connect, sizeof(Connect), 0, (sockaddr*)sender_addr, sender_addr_len))
        {
            std::cout<<"Could not send connection reply\n";
        }
    }
}
