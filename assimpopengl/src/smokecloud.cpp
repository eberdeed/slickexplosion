/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright (C) 2021  <copyright holder> <email>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "../include/smokecloud.h"

SmokeCloud::SmokeCloud(Shader *shader)
{
    this->shader = shader;
    cout << "\n\n\tCreating SmokeCloud.\n\n";
    tdata = chrono::system_clock::now();
    // Fill in particle data array
    srand ((long int)chrono::system_clock::to_time_t(tdata));
    // Create the data.
    generator = mt19937(rd());
    scaler = mat4(1.0);
    scaler = scale(scaler, vec3((float)SCALE, (float)SCALE, (float)SCALE));
    initFire();
    defineObjects();
}

SmokeCloud::~SmokeCloud()
{
    cout << "\n\n\tDestroying SmokeCloud.\n\n";
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
void SmokeCloud::initFire()
{
    bool isUnique = true;
    float r;
    cout << "\n\n\tIn initSound.\n\n";
    for (int i = 0; i < NUM_PARTICLES; i++ )
    {
        // Lifetime of particle
        particles[i].lifetime = (randomFloats(generator) * (3.0f * (float)EXP_GAP / 4.0f));
        particles[i].phi1 = randomFloats(generator) * pi180 * 2.0f;
        particles[i].rho1 = randomFloats(generator) * pi180 * 2.0f;
        r = (randomFloats(generator) / 2.0f) + 0.3f;
        particles[i].radius1 = glm::clamp(r, 0.3f, 6.0f);
    }
    if (true)
    {
        debug();
    }
    // Random color
    color = vec4(0.5f, 0.5f, 0.5f, 0.3f);
    if (debug1)
    {
        cout << "\n\n\tColor: " << color.r << ", " << color.g << ", " 
        << color.b << ", " <<  color.a;
    }
}    
void SmokeCloud::debug()
{
        for (int x = 0; x < NUM_PARTICLES; x++)
    {
        cout << "\n\tDisplacement phi:  " 
        << ", " << particles[x].phi1 << ", "
        << "\tDisplacement rho:  " << particles[x].rho1 << ", "
        << "\tRadius:  " << particles[x].radius1
        << "\tLifetime:  " << particles[x].lifetime;
    }
}

void SmokeCloud::drawCloud(mat4 model, mat4 view, mat4 projection, float timeVal, bool start)
{
    cout << "\n\tDrawing cloud with time " << timeVal << " and switch " << start;
    if (start)
    {
        glBindVertexArray(VAO);
        shader->Use();
        shader->setFloat("u_time", timeVal);
        shader->setVec4("u_color", color);
        shader->setMat4("model", model);
        shader->setMat4("view", view);
        shader->setMat4("projection", projection);
        shader->setMat4("scaler", scaler);
        glDrawArrays(GL_POINTS, 0, NUM_PARTICLES);
        glBindVertexArray(0);
    }
}    
void SmokeCloud::defineObjects()
{
    //Create vertex buffer.
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(particles), particles, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT,
    GL_FALSE, sizeof(ParticleData), (GLvoid*) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT,
    GL_FALSE, sizeof(ParticleData), (GLvoid*) sizeof(float));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 4, GL_FLOAT,
    GL_FALSE, sizeof(ParticleData), (GLvoid*) (2 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 4, GL_FLOAT,
    GL_FALSE, sizeof(ParticleData), (GLvoid*) (3 * sizeof(float)));
    glEnableVertexAttribArray(3);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
}
