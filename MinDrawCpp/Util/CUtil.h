/*
 * CUtil.h
 *
 *  Created on: 14 oct. 2022
 *      Author: Garnier
 */

#ifndef CUTIL_H_
#define CUTIL_H_


#include<SDL2/SDL.h>

class CUtil {
public:
	static int RenderDrawCircle(SDL_Renderer*pRenderer, SDL_Point ptCenter, int iRadius);
	static int RenderFillCircle(SDL_Renderer*pRenderer, SDL_Point ptCenter, int iRadius);

	static int RenderFillPolygon(SDL_Renderer*pRenderer, const SDL_Point*const pVertexes, int iVertexesCount);
	static SDL_Point GetPolygonCenter(const SDL_Point*const pVertexes, int iVertexesCount);

	static int RenderDrawTriangle(SDL_Renderer*pRenderer, SDL_Rect frame, int iRadius);
};


#endif /* CUTIL_H_ */
