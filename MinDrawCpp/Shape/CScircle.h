/*
 * CScircle.h
 *
 *  Created on: 30 oct. 2022
 *      Author: andre
 */

#ifndef CSCIRCLE_H_
#define CSCIRCLE_H_

#include<iostream>
#include<defines.h>
#include<SDL2/SDL.h>
#include<CShape.h>
#include<CUtil.h>

class CScircle : public CShape {
private:
	int m_toolType;
private:
	CScircle();
public:
	CScircle(SDL_Rect frame,SDL_Color color);
	virtual ~CScircle();
	virtual void Draw(SDL_Renderer*pRenderer)const;

	virtual void*WriteInFile(FILE*fd);
	virtual int GetType();
};

#endif /* CSCIRCLE_H_ */
