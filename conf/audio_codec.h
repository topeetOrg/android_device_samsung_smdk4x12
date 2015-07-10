/*
** Copyright 2008, The Android Open-Source Project
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/

#ifndef ANDROID_AUDIO_CODEC_H
#define ANDROID_AUDIO_CODEC_H

namespace android_audio_legacy {

typedef struct AudioMixer_tag {
    const char *ctl;
    const int   val;
} AudioMixer;

const AudioMixer device_out_SPK[] = {
	{"Left Output Mixer PCM Playback Switch", 1},
	{"Right Output Mixer PCM Playback Switch", 1},
	{"Speaker DC Volume", 5},
	{"Speaker AC Volume", 5},
	{"Speaker Playback Volume", 127},
	{"Headphone Playback Volume", 0},
    {NULL, NULL}
};
const AudioMixer device_out_RCV[] = {
    {NULL, NULL}
};
const AudioMixer device_out_RING_SPK[] = {
	{"Left Output Mixer PCM Playback Switch", 1},
	{"Right Output Mixer PCM Playback Switch", 1},
	{"Speaker DC Volume", 5},
	{"Speaker AC Volume", 5},
	{"Speaker Playback Volume", 127},
	{"Headphone Playback Volume", 0},
    {NULL, NULL}
};
const AudioMixer device_out_RING_NO_MIC[] = {
    {NULL, NULL}
};
const AudioMixer device_out_HP_NO_MIC[] = {
    {NULL, NULL}
};
const AudioMixer device_out_RING_HP[] = {
	{"Left Output Mixer PCM Playback Switch", 1},
	{"Right Output Mixer PCM Playback Switch", 1},
	{"Speaker DC Volume", 0},
	{"Speaker AC Volume", 0},
	{"Speaker Playback Volume", 0},
	{"Headphone Playback Volume", 127},
    {NULL, NULL}
};
const AudioMixer device_out_HP[] = {
	{"Left Output Mixer PCM Playback Switch", 1},
	{"Right Output Mixer PCM Playback Switch", 1},
	{"Speaker DC Volume", 0},
	{"Speaker AC Volume", 0},
	{"Speaker Playback Volume", 0},
	{"Headphone Playback Volume", 127},
    {NULL, NULL}
};
const AudioMixer device_out_RING_SPK_HP[] = {
	{"Left Output Mixer PCM Playback Switch", 1},
	{"Right Output Mixer PCM Playback Switch", 1},
	{"Speaker DC Volume", 5},
	{"Speaker AC Volume", 5},
	{"Speaker Playback Volume", 127},
	{"Headphone Playback Volume", 127},
    {NULL, NULL}
};
const AudioMixer device_out_SPK_HP[] = {
	{"Left Output Mixer PCM Playback Switch", 1},
	{"Right Output Mixer PCM Playback Switch", 1},
	{"Speaker DC Volume", 5},
	{"Speaker AC Volume", 5},
	{"Speaker Playback Volume", 127},
	{"Headphone Playback Volume", 127},
    {NULL, NULL}
};
const AudioMixer device_out_BT[] = {
    {NULL, NULL}
};
const AudioMixer device_out_OFF[] = {
	{"Left Output Mixer PCM Playback Switch", 0},
	{"Right Output Mixer PCM Playback Switch", 0},
	{"Speaker DC Volume", 0},
	{"Speaker AC Volume", 0},
	{"Speaker Playback Volume", 0},
	{"Headphone Playback Volume", 0},
    {NULL, NULL}
};

const AudioMixer device_voice_RCV[] = {
    {NULL, NULL}
};
const AudioMixer device_voice_SPK[] = {
	{"Left Output Mixer PCM Playback Switch", 1},
	{"Right Output Mixer PCM Playback Switch", 1},
	{"Speaker DC Volume", 5},
	{"Speaker AC Volume", 5},
	{"Speaker Playback Volume", 127},
	{"Headphone Playback Volume", 0},
    {NULL, NULL}
};
const AudioMixer device_voice_TTY_VCO[] = {
    {NULL, NULL}
};
const AudioMixer device_voice_TTY_HCO[] = {
    {NULL, NULL}
};
const AudioMixer device_voice_TTY_FULL[] = {
    {NULL, NULL}
};
const AudioMixer device_voice_HP_NO_MIC[] = {
    {NULL, NULL}
};
const AudioMixer device_voice_HP[] = {
	{"Left Output Mixer PCM Playback Switch", 1},
	{"Right Output Mixer PCM Playback Switch", 1},
	{"Speaker DC Volume", 0},
	{"Speaker AC Volume", 0},
	{"Speaker Playback Volume", 0},
	{"Headphone Playback Volume", 127},
    {NULL, NULL}
};
const AudioMixer device_voice_BT[] = {
    {NULL, NULL}
};
const AudioMixer device_voice_OFF[] = {
	{"Left Output Mixer PCM Playback Switch", 0},
	{"Right Output Mixer PCM Playback Switch", 0},
	{"Speaker DC Volume", 0},
	{"Speaker AC Volume", 0},
	{"Speaker Playback Volume", 0},
	{"Headphone Playback Volume", 0},
    {NULL, NULL}
};

const AudioMixer device_input_Main_Mic[] = {
	{"ADC PATH", 1},
	{"Capture Switch", 1},
	{"Capture Volume", 63},
	{"Left ADC Volume", 200},
	{"Right ADC Volume",200},
	{"ADC PCM Capture Volume", 127},
	{"Left Boost Mixer LINPUT1 Switch", 1},
	{"Right Boost Mixer RINPUT1 Switch", 1},
	{"Left Input Mixer Boost Switch", 1},
	{"Right Input Mixer Boost Switch", 1},
    {NULL, NULL}
};
const AudioMixer device_input_Hands_Free_Mic[] = {
	{"ADC PATH", 1},
	{"Capture Switch", 1},
	{"Capture Volume", 63},
	{"Left ADC Volume", 200},
	{"Right ADC Volume",200},
	{"ADC PCM Capture Volume", 127},
	{"Left Boost Mixer LINPUT1 Switch", 1},
	{"Right Boost Mixer RINPUT1 Switch", 1},
	{"Left Input Mixer Boost Switch", 1},
	{"Right Input Mixer Boost Switch", 1},
    {NULL, NULL}
};
const AudioMixer device_input_BT_Sco_Mic[] = {
    {NULL, NULL}
};
const AudioMixer device_input_MIC_OFF[] = {
	{"ADC PATH", 1},
	{"Capture Switch", 0},
	{"Capture Volume", 0},
	{"Left ADC Volume", 0},
	{"Right ADC Volume",0},
	{"ADC PCM Capture Volume", 0},
	{"Left Boost Mixer LINPUT1 Switch", 0},
	{"Right Boost Mixer RINPUT1 Switch", 0},
	{"Left Input Mixer Boost Switch", 0},
	{"Right Input Mixer Boost Switch", 0},
    {NULL, NULL}
};

}; // namespace android

#endif //ANDROID_AUDIO_CODEC_H
