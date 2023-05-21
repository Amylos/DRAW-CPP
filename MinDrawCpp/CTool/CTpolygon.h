/*
 * CTpolygon.h
 *
 *  Created on: 14 oct. 2022
 *      Author: Garnier
 */

#ifndef CTPOLYGON_H_
#define CTPOLYGON_H_

#include<iostream>
#include<SDL2/SDL.h>
#include<defines.h>
#include<CTool.h>
#include<CUtil.h>

class CTpolygon : public CTool{
private:
	int m_toolType;
	SDL_Point	m_vertices[7];
	CTpolygon();
public:
	CTpolygon(SDL_Color color);
	virtual ~CTpolygon();

	virtual void*Move(SDL_Rect*frame);
	virtual void SetFrame(SDL_Rect frame);
	virtual void Draw(SDL_Renderer*pRenderer)const;
	virtual int GetType();
};

#endif /* CTPOLYGON_H_ */
