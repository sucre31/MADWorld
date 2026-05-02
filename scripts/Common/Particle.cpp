#include "Particle.h"
#include <DxLib.h>
#include <algorithm>
#include <cmath>

static void HSVtoRGB(float h, float s, float v, int& r, int& g, int& b)
{
    int i = (int)(h * 6.0f);
    float f = h * 6.0f - i;

    float p = v * (1.0f - s);
    float q = v * (1.0f - f * s);
    float t = v * (1.0f - (1.0f - f) * s);

    switch (i % 6) {
    case 0: r = v * 255; g = t * 255; b = p * 255; break;
    case 1: r = q * 255; g = v * 255; b = p * 255; break;
    case 2: r = p * 255; g = v * 255; b = t * 255; break;
    case 3: r = p * 255; g = q * 255; b = v * 255; break;
    case 4: r = t * 255; g = p * 255; b = v * 255; break;
    case 5: r = v * 255; g = p * 255; b = q * 255; break;
    }
}

ParticleEmitter::ParticleEmitter() {
    //setRandomColor();
}

void ParticleEmitter::setPosition(float px, float py)
{
    x = px;
    y = py;
}


void ParticleEmitter::spawn(int count, float accel) {
    for (int i = 0; i < count; i++) {
        SimpleParticle p;

        p.x = x;
        p.y = y;

        float angle = GetRand(360) * DX_PI_F / 180.0f;
        float speed = 0.5f + (GetRand(100) / 100.0f) * 2.0f;

        // accelで少し強化
        speed *= (0.5f + accel);

        p.vx = cosf(angle) * speed;
        p.vy = sinf(angle) * speed;

        p.life = 0.0f;
        p.maxLife = 0.3f + (GetRand(100) / 100.0f) * 0.4f;

        p.size = 0.5f + (GetRand(100) / 100.0f) * 0.5f;

        p.rot = 0.0f;
        p.rotSpeed = (GetRand(100) / 100.0f - 0.5f) * 0.2f;

        p.baseAlpha = 0.7f + (GetRand(100) / 100.0f) * 0.3f;

        int r = GetRand(100);
        if (r < 60) p.type = 0;
        else if (r < 90) p.type = 1;
        else p.type = 2;

        particles.push_back(p);
    }
}

void ParticleEmitter::update(float dt, float accel) {
    globalHue += dt * 0.05f; // 超ゆっくり
    if (globalHue > 1.0f) globalHue -= 1.0f;

    // 発生制御（暴走防止）
    spawnTimer += dt;

    currentAccel = accel;

    float emitScale = 0.0f;

    if (accel > 0.2f)
    {
        emitScale = (accel - 0.2f) / (1.0f - 0.2f);
    }
    emitScale = std::clamp(emitScale, 0.0f, 1.0f);

    if (emitScale <= 0.01f)
    {
        spawnTimer = 0.0f;
    }
    else {
        float interval = 0.05f;
        interval /= (1.0f + accel * emitScale);

        while (spawnTimer >= interval)
        {
            spawnTimer -= interval;
            spawn(1, accel);
        }
    }

    for (auto& p : particles) {
        p.x += p.vx * 60.0f * dt;
        p.y += p.vy * 60.0f * dt;

        p.rot += p.rotSpeed * 60.0f * dt;
        p.life += dt;
    }

    particles.erase(
        std::remove_if(particles.begin(), particles.end(),
            [](const SimpleParticle& p) {
                return p.life >= p.maxLife;
            }),
        particles.end()
    );
}
void ParticleEmitter::draw(int imgSmall, int imgMiddle, int imgBig) const {

    float hue = globalHue;

    if (!syncColor) {
        hue += 0.15f;
        if (hue > 1.0f) hue -= 1.0f;
    }

    int cr, cg, cb;
    HSVtoRGB(hue, 0.8f, 1.0f, cr, cg, cb);

    SetDrawBright(cr, cg, cb);

    for (const auto& p : particles) {

        float t = p.life / p.maxLife;
        if (t > 1.0f) continue;

        float fade = (1.0f - t);

        int alpha = (int)(255 * fade * p.baseAlpha * (0.3f + currentAccel));
        alpha = std::clamp(alpha, 0, 255);

        int handle = imgSmall;
        if (p.type == 1) handle = imgMiddle;
        if (p.type == 2) handle = imgBig;

        SetDrawBlendMode(DX_BLENDMODE_ADD, alpha);

        DrawRotaGraph(
            (int)p.x,
            (int)p.y,
            p.size,
            p.rot,
            handle,
            TRUE
        );
    }

    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    SetDrawBright(255, 255, 255);
}

void ParticleEmitter::setRandomColor()
{
    // 0.0f ～ 1.0f の範囲でランダム
    globalHue = static_cast<float>(GetRand(100)) /100.0f;
}