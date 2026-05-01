#pragma once
#include <vector>

struct SimpleParticle {
    float x, y;
    float vx, vy;

    float life;
    float maxLife;

    float size;
    float rot;
    float rotSpeed;

    int type; // 0 small, 1 middle, 2 big
    float baseAlpha;
};


class ParticleEmitter {
public:
    void setPosition(float px, float py);

    void update(float dt, float accel);
    void draw(int imgSmall, int imgMiddle, int imgBig) const;

private:
    float currentAccel = 0.0f;
    float globalHue = 0.0f;   // 全体時間で変化する色
    bool syncColor = true;    // trueなら全員同色、falseなら個別

    static const int MAX_PARTICLES = 200;

    std::vector<SimpleParticle> particles;

    float spawnTimer = 0.0f;

    float x = 0;
    float y = 0;

    void spawn(int count, float accel);
};