#ifndef _hijack_h_
#define _hijack_h_

#include <D3D11_4.h>

void hijack(ID3D11DeviceContext *context);
void hijackGl();
ID3D11Texture2D *getDepthTextureMatching(ID3D11Texture2D *tex);
void flushTextureLatches();

#endif