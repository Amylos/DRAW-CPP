/*
 * CSrectangle.h
 *
 *  Created on: 30 oct. 2022
 *      Author: andre
 */

#ifndef CSRECTANGLE_H_
#define CSRECTANGLE_H_

#include<iostream>
#include<SDL2/SDL.h>
#include<defines.h>
#include<CShape.h>

class CSrectangle : public CShape {
private:
	int m_toolType;
private:
	CSrectangle();
public:
	CSrectangle(SDL_Rect frame,SDL_Color color);
	virtual ~CSrectangle();

	virtual void Draw(SDL_Renderer*pRenderer)const;
	virtual void*WriteInFile(FILE*fd);
	virtual int GetType();
};

#endif /* CSRECTANGLE_H_ */



