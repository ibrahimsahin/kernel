#include <rand.h>

unsigned int m_w = 143;
unsigned int m_z = 341;

int rand(){
    int res;
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    res=(int)(m_z << 16) + m_w;
    if(res<0)res *= -1;
    return res;
}
