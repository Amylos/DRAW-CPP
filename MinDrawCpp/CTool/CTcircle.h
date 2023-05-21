/*
 * CTcircle.h
 *
 *  Created on: 11 oct. 2022
 *      Author: Garnier
 */

#ifndef CTCIRCLE_H_
#define CTCIRCLE_H_

#include<iostream>
#include<SDL2/SDL.h>
#include<CTool.h>
#include<CUtil.h>

class CTcircle : public CTool{
private:
	int m_toolType;
	CTcircle();
public:
	CTcircle(SDL_Color color);
	virtual ~CTcircle();
	virtual void Draw(SDL_Renderer*pRenderer)const;
	virtual int GetType();
};

#endif /* CTCIRCLE_H_ */
