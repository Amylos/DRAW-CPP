/*
 * CTpolygon.cpp
 *
 *  Created on: 14 oct. 2022
 *      Author: Garnier
 */


#include <CTpolygon.h>

CTpolygon::CTpolygon(): CTool(),m_toolType(0){}

CTpolygon::~CTpolygon(){}

CTpolygon::CTpolygon(SDL_Color color): CTool(color),m_toolType(TOOL_POLYGON){}


void CTpolygon::SetFrame(SDL_Rect frame){

	CTool::SetFrame(frame);
	m_vertices[0] = SDL_Point{frame.x,  frame.y + frame.w*1/2};
	m_vertices[1] = SDL_Point{frame.x + frame.w * 1/5,frame.y + frame.w};
	m_vertices[2] = SDL_Point{frame.x + frame.w ,frame.y + frame.w*4/5};
	m_vertices[3] = SDL_Point{frame.x + frame.w* 4/5,frame.y};
	m_vertices[4] = SDL_Point{frame.x + frame.w/2,frame.y + frame.h/2};
	m_vertices[5] = SDL_Point{frame.x + frame.w*4/5, frame.y + frame.h*7/10};
	m_vertices[6] = m_vertices[0];
}

void CTpolygon::Draw(SDL_Renderer*pRenderer)const{
	SDL_SetRenderDrawColor(pRenderer, m_color.r, m_color.g, m_color.b, m_color.a);
	SDL_RenderDrawLines(pRenderer, m_vertices, 7);
}

void*CTpolygon::Move(SDL_Rect*frame){
	CTool::Move(frame);

	m_vertices[0] = SDL_Point{frame->x , 										frame->y + frame->w*(frame->h-1) + (frame->w -APP_TOOL_PADDING)*1/2 };
	m_vertices[1] = SDL_Point{frame->x +  (frame->w -APP_TOOL_PADDING)*1/5,		frame->y + frame->w*(frame->h-1) + (frame->w -APP_TOOL_PADDING) };
	m_vertices[2] = SDL_Point{frame->x +  (frame->w -APP_TOOL_PADDING) ,		frame->y + frame->w*(frame->h-1) + (frame->w -APP_TOOL_PADDING)*4/5 };
	m_vertices[3] = SDL_Point{frame->x +  (frame->w -APP_TOOL_PADDING)*4/5,		frame->y + frame->w*(frame->h-1) };
	m_vertices[4] = SDL_Point{frame->x +  (frame->w -APP_TOOL_PADDING)*1/2,		frame->y + frame->w*(frame->h-1) + (frame->w -APP_TOOL_PADDING)*1/2};
	m_vertices[5] = SDL_Point{frame->x +  (frame->w -APP_TOOL_PADDING)*4/5,		frame->y + frame->w*(frame->h-1) +  (frame->w -APP_TOOL_PADDING)*7/10 };
	m_vertices[6] = m_vertices[0];

	return nullptr;
}

int CTpolygon::GetType(){
	 return m_toolType;
}

