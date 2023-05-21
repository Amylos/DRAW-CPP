/*
 * CTtriangle.h
 *
 *  Created on: 11 oct. 2022
 *      Author: Garnier
 */

#ifndef CTTRIANGLE_H_
#define CTTRIANGLE_H_

#include<iostream>
#include<SDL2/SDL.h>
#include<CArea.h>
#include<CTool.h>
#include<CUtil.h>

class CTtriangle : public CTool {
private:
	int m_toolType;
	SDL_Point m_vertices[4];
	CTtriangle();
public:
	CTtriangle(SDL_Color color);
	virtual ~CTtriangle();
	virtual void Draw(SDL_Renderer*pRenderer)const;
	virtual int GetType();
};

#endif /* CTTRIANGLE_H_ */
