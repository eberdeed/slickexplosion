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
    cout << "\n\texplosion is " << explosion;
    if (!explosion)
    {
        timeend = chrono::system_clock::now();
        gap = (int) chrono::duration_cast<chrono::milliseconds>(
        timeend - timestart).count();
        if ((thread != NULL) && (expStarted))
        {
            SDL_DetachThread(thread);
            expStarted = false;
            timestart = chrono::system_clock::now();
        }
        cout << "\n\tShip drawn.";
        object->Draw(view, projection, objectinfo, lights, spotLights, viewPos);
    }
    else
    {
        cout << "\n\tExplosion drawn.";
        /* Simply create a thread */
        if(!expStarted)
        {
            thread = SDL_CreateThread((SDL_ThreadFunction)ExplodeIt::sndMaker, "SoundThread", (void *)NULL);
            timestart = chrono::system_clock::now();
            expStarted = true;
            SDL_Delay(EXP_GAP);
            object->DrawExplosion(0, model, view, projection);

        }
        else
        {
            object->DrawExplosion(0, model, view, projection);
        }
        timeVal = (float) gap;


    }
}

char *ExplodeIt::sndMaker()
{
    char threadname[40];
    chrono::system_clock::time_point threadbegin, threadend;
    Uint32 wave_len; // length of our sample
    Uint8 *wave_buf; // buffer containing our audio file
    SDL_AudioSpec wave_spec, ret_spec; // the specs of our piece of music
    strcpy(threadname, "Sound Interval:   ");
    cout << "\n\n\tStarting sound production.\n\n";
    threadbegin = chrono::system_clock::now();
    cout << "\n\n\tLoading WAV file.\n\n";
    
    if (SDL_LoadWAV(explosionSound, &wave_spec, &wave_buf, &wave_len) ==  NULL)
    {
        cout << "\n\n\tUnable to load WAV file:  " << SDL_GetError() << "\n\n";
        exit(-1);
    }
    else
    {
        cout << "\n\n\tWAV file successfully loaded.\n\n";
    }
	// set the callback function
	/*
	wave_spec.callback = ShipFrager::my_audio_callback;
	wave_spec.userdata = NULL;
	// set our global static variables
	audio_buf = wave_buf; // copy sound buffer
	audio_len = wave_len; // copy file length
	*/
    string name  = SDL_GetAudioDeviceName(0, 0);
    SDL_AudioDeviceID dev = SDL_OpenAudioDevice(name.c_str(), 0, &wave_spec, &ret_spec, SDL_AUDIO_ALLOW_FORMAT_CHANGE);
    if (dev < 0)
    {
        cout << "\n\n\tUnable to open audio device:  " << SDL_GetError() << "\n\n";
        exit(-1);
    }
    else
    {
        cout << "\n\n\tAudio device successfully opened.\n\n";
        int result = SDL_QueueAudio(dev, wave_buf, wave_len);
        if (result != 0)
        {
            cout <<  "\n\n\tUnable to queue audio data.\n\n";
            exit(-1);
        }
        else
        {
            cout << "\n\n\tAudio data successfully queued.\n\n";
        }
    }
    SDL_PauseAudioDevice(dev, 0); /* start audio playing. */
    cout << "\n\n\tPlayed the audio.\n\n";
    SDL_Delay(11340); /* let the audio callback play some sound for 5 seconds. */
    SDL_CloseAudioDevice(dev);
    cout << "\n\n\tClosed audio device.\n\n";
	SDL_FreeWAV(wave_buf);
    threadend = chrono::system_clock::now();
    stringstream ss;
    int ttime = chrono::duration_cast<chrono::milliseconds>(threadend -
    threadbegin).count();
    ss << ttime;
    strcat(threadname, ss.str().c_str());
    return threadname;
}
