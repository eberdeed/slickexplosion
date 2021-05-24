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

#include "../include/explodeit.h"

ExplodeIt::ExplodeIt()
{
    cout << "\n\n\tCreating ExplodeIt.\n\n";
    initObject();
}

ExplodeIt::~ExplodeIt()
{
    cout << "\n\n\tDestroying ExplodeIt.\n\n";
    delete shader;
    delete explodeShader;
    delete cloudShader;
    delete object;
}

void ExplodeIt::initObject()
{
    shader = new Shader();
    shader->initShader(objectVertex, objectFragment, "blowitup.bin");
    explodeShader = new Shader();
    explodeShader->initShader(explodeVertex, explodeFragment, "banger.bin");
    cloudShader = new Shader();
    cloudShader->initShader(cloudVertex, cloudFragment, "cloud.bin");
    item.path = objectLoc;
    item.model = mat4(1.0f);
    item.location = vec3(0.0f);
    item.gamma = 2.0f;
    item.idval = 0;
    objectinfo.push_back(item);
    object = new Model(objectinfo, shader, explodeShader, cloudShader, 2);
}

void ExplodeIt::drawIt(mat4 model, mat4 view, mat4 projection, vec3 viewPos, bool explosion)
{
    objectinfo[0].model = model;
    //terrain->drawTerrain(model, view, projection);
    if (!explosion)
    {
        object->zeroTime();
        object->Draw(0, view, projection, objectinfo, lights, spotLights, viewPos);
    }
    else
    {
        object->DrawExplosion(0, view, projection, objectinfo);
    }
}

