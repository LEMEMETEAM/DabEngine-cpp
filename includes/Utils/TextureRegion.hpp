#ifndef TEXTUREREGION_H_
#define TEXTUREREGION_H_

class TextureRegion
{
    public:
        float m_scaleX, m_scaleY;
        float m_u, m_v, m_s, m_t;
        int m_tileNomX, m_tileNomY;
        TextureRegion(int tileNomX = 0, int tileNomY = 0)
        :m_scaleX(1.0f/(float)tileNomX), m_scaleY(1.0f/(float)tileNomY),
        m_u(0), m_v(0), m_s(m_scaleX), m_t(m_scaleY),
        m_tileNomX(tileNomX), m_tileNomY(tileNomY)
        {}

        inline TextureRegion setTile(int tileposx, int tileposy)
        {
            m_u = ((tileposx - 1) * m_scaleX);
            m_v = (tileposy - 1) * m_scaleY;
            m_s = m_u + m_scaleX;
            m_t = m_v + m_scaleY;
            return *this;
        }

        inline TextureRegion setTile(int xmin, int xmax, int ymin, int ymax)
        {
            m_u = ((xmin - 1) * m_scaleX);
            m_v = ((ymin - 1) * m_scaleY);
            m_s = ((xmax - 1) * m_scaleX) + m_scaleX;
            m_t = ((ymax - 1) * m_scaleY) + m_scaleY;
            return *this;
        }

        inline TextureRegion setUV(int u, int v, int s, int t)
        {
            m_u = u;
            m_v = v;
            m_s = s;
            m_t = t;
            return *this;
        }
};

#endif