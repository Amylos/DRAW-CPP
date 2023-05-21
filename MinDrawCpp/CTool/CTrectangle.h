/*
 * CTrectangle.h
 *
 *  Created on: 11 oct. 2022
 *      Author: Garnier
 */

#ifndef CTRECTANGLE_H_
#define CTRECTANGLE_H_



#include<iostream>
#include<SDL2/SDL.h>
#include<defines.h>
#include<CTool.h>

class CTrectangle : public CTool{
private:
	int m_toolType;
	CTrectangle();
public:
	~CTrectangle();
	CTrectangle(SDL_Color color);
	virtual void Draw(SDL_Renderer*pRenderer)const;
	virtual int GetType();
};

#endif /* CTRECTANGLE_H_ */
