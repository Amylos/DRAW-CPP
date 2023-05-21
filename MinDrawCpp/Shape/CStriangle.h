/*
 * CStriangle.h
 *
 *  Created on: 30 oct. 2022
 *      Author: andre
 */

#ifndef CSTRIANGLE_H_
#define CSTRIANGLE_H_


#include<iostream>
#include<SDL2/SDL.h>
#include<defines.h>
#include<CShape.h>
#include<CUtil.h>

class CStriangle : public CShape {
private:
	int m_toolType;
private:
	CStriangle();
public:
	CStriangle(SDL_Rect frame,SDL_Color color);
	virtual ~CStriangle();
	virtual void Draw(SDL_Renderer*pRenderer)const;
	virtual void*WriteInFile(FILE*fd);
	virtual int GetType();
};

#endif /* CSTRIANGLE_H_ */


