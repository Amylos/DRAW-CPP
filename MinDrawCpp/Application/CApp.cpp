/*
 * CApp.cpp
 *
 *  Created on:  2022
 *      Author: Garnier
 */


#include"CApp.h"

using namespace std;

#define mBitsSet(f,m)		((f)|=(m))
#define mBitsClr(f,m)		((f)&=(~(m)))
#define mBitsTgl(f,m)		((f)^=(m))
#define mBitsMsk(f,m)		((f)& (m))
#define mIsBitsSet(f,m)		(((f)&(m))==(m))
#define mIsBitsClr(f,m)		(((~(f))&(m))==(m))


enum s_statusMasks{
	ST_ALL_CLEARED				= 0x00000000,
	ST_APP_INIT_FAILED			= 0x80000000,
	ST_APP_SDL_INITIATED		= 0x00000001,
	ST_APP_MOUSE_BUTTON_DOWN	= 0x00000002,
	ST_APP_PAUSED				= 0x00000004,
	ST_APP_MOVE_TOOLBOX			= 0x00000008,
    ST_APP_IS_DRAWING       	= 0x00000010,
    ST_APP_LCTRL_PRESSED    	= 0x00000020,
	ST_APP_LSHIFT_PRESSED   	= 0x00000040,
	ST_APP_RIGHT_PRESSED		= 0x00000080,

};

const char*toolTypeStrs[]={
    "UNDEFINED",    /* @offset 0*/
    "CIRCLE",       /* @offset 1*/
    "", /* NOT USED */
    "", /* NOT USED */
    "TRIANGLE",     /* @offset 4*/
    "SQUARE",       /* @offset 5*/
    "", /* NOT USED */
    "POLYGON",      /* @offset 7*/
    "COLORCHART"    /* @offset 8*/
};


using namespace std;

Uint32 _AppTimerCallback(Uint32 interval, void* pParam);

/**************************** CAPP METHOD ****************************/


/**************************** CONSTRUCTEUR ****************************/



CApp::CApp():
		m_uStatus(ST_ALL_CLEARED),
		m_rFrame(SDL_Rect{0}),
		m_pTitle(nullptr),
		m_pWindow(nullptr),
		m_pRenderer(nullptr),
		m_colorBackground(SDL_Color{0}),
		m_timerID(0),
		m_pSelectedTool(nullptr),
		m_SelectedColor(SDL_Color{0}),
		m_pVertexes(nullptr),
	    m_iVertexesNumber(0),
		m_iVertexesCapacity(0),
		m_ShapeOnMouse(nullptr)
{}


/************************ CONSTRUCTEUR SURCHARGE ***********************/


CApp::CApp(const char* pTitle, int iWidth, int iHeight, SDL_Color color):
		m_uStatus(ST_ALL_CLEARED),
		m_rFrame(SDL_Rect{0,0,iWidth,iHeight}),
		m_pTitle(new char [strlen(pTitle)+1]),
		m_pWindow(nullptr),
		m_pRenderer(nullptr),
		m_colorBackground(color),
		m_timerID(0),
		m_pSelectedTool(nullptr),
		m_SelectedColor(APP_TOOL_COLOR),
		m_pVertexes(nullptr),
	    m_iVertexesNumber(0),
		m_iVertexesCapacity(0)
{
	strcpy(m_pTitle,pTitle);

	srand((unsigned int)time(NULL));

	if(SDL_Init(SDL_INIT_VIDEO)!=0){
		cerr << "Failed to initiate SDL :" << SDL_GetError() << endl;
		mBitsSet(m_uStatus,ST_APP_INIT_FAILED);
		return;
	}
	mBitsSet(m_uStatus,ST_APP_SDL_INITIATED);

	m_pWindow = SDL_CreateWindow(APP_WINDOW_TITLE,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			APP_WINDOW_WIDTH,
			APP_WINDOW_HEIGHT,
			SDL_WINDOW_SHOWN);

	if(m_pWindow == NULL){
		cerr << " Failed to create window :" << SDL_GetError() << endl;
		mBitsSet(m_uStatus,ST_APP_INIT_FAILED);
		return;
	}

	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);

	if(m_pRenderer == NULL){
		cerr << "Failed to create accelerated renderer" << SDL_GetError() << endl;
		mBitsSet(m_uStatus,ST_APP_INIT_FAILED);
		return;
	}


	m_toolbox.AddTool(new CTrectangle(m_SelectedColor));
	m_toolbox.AddTool(new CTcircle(m_SelectedColor));
	m_toolbox.AddTool(new CTtriangle(m_SelectedColor));
	m_toolbox.AddTool(new CTpolygon(m_SelectedColor));
	m_toolbox.AddTool(new CTcolorChart{m_SelectedColor,m_pRenderer,APP_TOOLBOX_COLORCHART_FILE});



	m_canvas.Unserialize();
	if(int res = Run()){
		cerr << "Application Failed" << res << endl;
	}
}

/******************************* DESTRUCTEUR *****************************/

CApp::~CApp(){

	if(m_pRenderer) SDL_DestroyRenderer(m_pRenderer);
	if(m_pWindow)	SDL_DestroyWindow(m_pWindow);

	SDL_Quit();
}

/************************* RUN FUNCTION  ******************************/

int CApp::Run(){
	if(mIsBitsSet(m_uStatus,ST_APP_INIT_FAILED))	return EXIT_FAILURE;

	m_timerID = SDL_AddTimer(APP_ANIMATE_RATE, (SDL_TimerCallback)_AppTimerCallback, nullptr);
	srand(time(NULL));

	int iQuit = 0;
	SDL_Event event;
	char buf[256];

	while(!iQuit){
		if(SDL_WaitEvent(&event)){
			switch (event.type) {
			case SDL_APP_CALLBACK_EVENT:
				Draw();
				break;
			case SDL_MOUSEBUTTONDOWN:
				switch(event.button.button){
				case SDL_BUTTON_LEFT:
					if(mIsBitsSet(m_uStatus,ST_APP_LCTRL_PRESSED) && mIsBitsClr(m_uStatus,ST_APP_IS_DRAWING)){
						m_pSelectedTool = nullptr;
						if(m_ShapeOnMouse){
							SDL_Log("COPY");
							switch(m_ShapeOnMouse->GetType()){
							case TOOL_CIRCLE:
								m_canvas.AddShape(new CScircle(SDL_Rect{m_ShapeOnMouse->GetFrame().x,
																		m_ShapeOnMouse->GetFrame().y,
																		m_ShapeOnMouse->GetFrame().w,
																		m_ShapeOnMouse->GetFrame().h},
																		m_ShapeOnMouse->GetColor()));
								break;
							case TOOL_RECTANGLE:
								m_canvas.AddShape(new CSrectangle(SDL_Rect{m_ShapeOnMouse->GetFrame().x,
																		m_ShapeOnMouse->GetFrame().y,
																		m_ShapeOnMouse->GetFrame().w,
																		m_ShapeOnMouse->GetFrame().h},
																		m_ShapeOnMouse->GetColor()));
								break;
							case TOOL_TRIANGLE:
								m_canvas.AddShape(new CStriangle(SDL_Rect{m_ShapeOnMouse->GetFrame().x,
																		m_ShapeOnMouse->GetFrame().y,
																		m_ShapeOnMouse->GetFrame().w,
																		m_ShapeOnMouse->GetFrame().h},
																		m_ShapeOnMouse->GetColor()));
								break;
							case TOOL_POLYGON:
								m_ShapeOnMouse->GetpVertexes();

								SDL_Point*VertexesCopy  = (SDL_Point*)malloc(sizeof(SDL_Point)*m_ShapeOnMouse->GetiVertexes());

								for(int k =0; k<m_ShapeOnMouse->GetiVertexes() ;++k){
									VertexesCopy[k] = m_ShapeOnMouse->GetpVertexes()[k];
								}
								m_canvas.AddShape(new CSpolygon(SDL_Rect{m_ShapeOnMouse->GetFrame().x,
																		m_ShapeOnMouse->GetFrame().y,
																		m_ShapeOnMouse->GetFrame().w,
																		m_ShapeOnMouse->GetFrame().h},
																		m_SelectedColor,m_ShapeOnMouse->GetiVertexes(),VertexesCopy));
								break;

							}
						}
					}
					SDL_Log("SDL_BUTTON_LEFT");
					if(m_toolbox.MouseOnToolBox(SDL_Point{event.button.x,event.button.y})){
						sprintf(buf,"TOOLBOX");
						if((m_pSelectedTool = m_toolbox.ToolAt(SDL_Point{event.button.x,event.button.y}))){
							sprintf(buf,"TOOLBOX : ,%d %s",m_pSelectedTool->GetType(),toolTypeStrs[m_pSelectedTool->GetType()]);
							if(m_pSelectedTool->GetType() == TOOL_COLORCHART){
								/**** NOT FINISHED ****/
								m_SelectedColor = m_pSelectedTool->GetColorChart(SDL_Point{event.button.x,event.button.y});
							}
						}
						else{
							m_pSelectedTool = nullptr;
						}
					}
					else{
						if(m_pSelectedTool){
							sprintf(buf,"CANVAS : ,%d %s",m_pSelectedTool->GetType(),toolTypeStrs[m_pSelectedTool->GetType()]);
						}
						else	sprintf(buf,"CANVAS");
						if(m_pSelectedTool){
							m_ptStart = m_ptEnd = SDL_Point{event.button.x,event.button.y};
							if(m_pSelectedTool->GetType() == TOOL_POLYGON){
								/***** TOOL VERTEXES****/
								 if(mIsBitsClr(m_uStatus, ST_APP_IS_DRAWING)){
									m_iVertexesNumber=0;
									m_iVertexesCapacity =10;
									m_pVertexes = (SDL_Point*)malloc(sizeof(SDL_Point)*m_iVertexesCapacity);
									assert(m_pVertexes);
								}
								m_pVertexes[m_iVertexesNumber]=m_ptStart;
								if(++m_iVertexesNumber>=m_iVertexesCapacity){
									m_iVertexesCapacity*=1.5;
									m_pVertexes = (SDL_Point*)realloc(m_pVertexes,sizeof(SDL_Point)*m_iVertexesCapacity);
									assert(m_pVertexes);
								}
							}
							mBitsSet(m_uStatus,ST_APP_IS_DRAWING);
						}
					}
					SDL_SetWindowTitle(m_pWindow, buf);
					break;
				case SDL_BUTTON_RIGHT:
					SDL_Log("SDL_BUTTON_RIGHT");
					mBitsSet(m_uStatus,ST_APP_RIGHT_PRESSED);
					if(mIsBitsSet(m_uStatus,ST_APP_LCTRL_PRESSED))  m_canvas.DeleteShape(SDL_Point{event.button.x,event.button.y});
					break;
				default:
					 break;
				}
			break;
				break;

			case SDL_MOUSEBUTTONUP:
				switch(event.button.button){
				case SDL_BUTTON_LEFT:
					SDL_Log("SDL_BUTTON_LEFT");
					if(m_toolbox.MouseOnToolBox(SDL_Point{event.button.x,event.button.y}))	break;
						if(m_pSelectedTool){
							m_ptEnd = SDL_Point{event.button.x,event.button.y};
							switch(m_pSelectedTool->GetType()){ /*ADDING SHAPES*/

							case TOOL_TRIANGLE:
								m_canvas.AddShape(new CStriangle(SDL_Rect{SetRightWay(m_ptStart, m_ptEnd).x,SetRightWay(m_ptStart, m_ptEnd).y,SDL_abs(m_ptStart.x-m_ptEnd.x),SDL_abs(m_ptStart.y-m_ptEnd.y)},m_SelectedColor));
								mBitsClr(m_uStatus, ST_APP_IS_DRAWING);
								break;
							case TOOL_RECTANGLE:
								m_canvas.AddShape(new CSrectangle(SDL_Rect{SetRightWay(m_ptStart, m_ptEnd).x,SetRightWay(m_ptStart, m_ptEnd).y,SDL_abs(m_ptStart.x-m_ptEnd.x),SDL_abs(m_ptStart.y-m_ptEnd.y)},m_SelectedColor));
								mBitsClr(m_uStatus, ST_APP_IS_DRAWING);
								break;
							case TOOL_CIRCLE:
								m_canvas.AddShape(new CScircle(SDL_Rect{SetRightWay(m_ptStart, m_ptEnd).x,SetRightWay(m_ptStart, m_ptEnd).y,SDL_abs(m_ptStart.x-m_ptEnd.x),SDL_abs(m_ptStart.y-m_ptEnd.y)},m_SelectedColor));
								mBitsClr(m_uStatus, ST_APP_IS_DRAWING);
							case TOOL_POLYGON:
								if(mIsBitsSet(m_uStatus, ST_APP_LCTRL_PRESSED)){ /* this is the way to end a polygon drawing, Left CTRL key must be pressed */
									m_pVertexes[m_iVertexesNumber]=m_ptEnd;
									m_iVertexesNumber++;
									m_canvas.AddShape(new CSpolygon(SDL_Rect{0,0,0,0},m_SelectedColor,m_iVertexesNumber,m_pVertexes));
									free(m_pVertexes);
									mBitsClr(m_uStatus, ST_APP_IS_DRAWING);
								}
								break;
							case TOOL_COLORCHART:
								 mBitsClr(m_uStatus, ST_APP_IS_DRAWING);
							default:
								break;
							}
						}
						break;
				case SDL_BUTTON_RIGHT:
					SDL_Log("SDL_BUTTON_RIGHT");
					mBitsClr(m_uStatus,ST_APP_RIGHT_PRESSED);
					break;
				default:
					 break;
				}
				break;
			break;
			case SDL_MOUSEMOTION:
				if(m_canvas.ShapeIsAt(SDL_Point{event.button.x,event.button.y})){
					m_ShapeOnMouse = m_canvas.ShapeIsAt(SDL_Point{event.button.x,event.button.y});
				}
				else{
					m_ShapeOnMouse = nullptr;
				}
				if(mIsBitsSet(m_uStatus,ST_APP_RIGHT_PRESSED)){
					if(m_ShapeOnMouse){
						m_canvas.DragMethod(m_ShapeOnMouse, SDL_Point{event.motion.xrel,event.motion.yrel});
					}
				}
				if(mIsBitsSet(m_uStatus,ST_APP_MOVE_TOOLBOX)){
					m_toolbox.MouseMotion(&event.motion);
				}
				if(mIsBitsSet(m_uStatus, ST_APP_IS_DRAWING)){
				  m_ptEnd=(SDL_Point){event.motion.x, event.motion.y};
				  {
					int iXmouse=event.motion.x, iYmouse=event.motion.y, iClip=0;
					if(event.motion.x<m_canvas.GetFrame().x){
						iXmouse=m_canvas.GetFrame().x;
						iClip=1;
					}
					if(event.motion.x>m_canvas.GetFrame().x+m_canvas.GetFrame().w){
						iXmouse=m_canvas.GetFrame().x+m_canvas.GetFrame().w;
						iClip=1;
					}
					if(event.motion.y<m_canvas.GetFrame().y){
						iYmouse=m_canvas.GetFrame().y;
						iClip=1;
					}
					if(event.motion.y>m_canvas.GetFrame().y+m_canvas.GetFrame().h){
						iYmouse=m_canvas.GetFrame().y+m_canvas.GetFrame().h;
						iClip=1;
					}
					if(iClip) SDL_WarpMouseInWindow(m_pWindow, iXmouse, iYmouse);
				}
			  }
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					event.type=SDL_QUIT;
					SDL_PushEvent(&event);
					break;
				case SDLK_f:
					m_canvas.Flush();
					break;
				case SDLK_LCTRL:
					mBitsSet(m_uStatus, ST_APP_LCTRL_PRESSED);
					break;
				case SDLK_p:
					mBitsTgl(m_uStatus,ST_APP_PAUSED);
					break;
				case SDLK_m:
					mBitsTgl(m_uStatus,ST_APP_MOVE_TOOLBOX);
					break;
				case SDLK_s: /******* SERIALIZE ********/
					m_canvas.Serialize();
					break;
				case SDLK_u: /*** UN SERIALIZE FILE TO CONTAINER ***/
					m_canvas.Unserialize();
					break;
				default:
					break;
				}
				break;
			case SDL_KEYUP:
				switch(event.key.keysym.sym){
				case SDLK_LCTRL:
					mBitsClr(m_uStatus, ST_APP_LCTRL_PRESSED);
					break;
				default:
					break;
				}
			    break;
			case SDL_QUIT:
				iQuit=1;
				break;
			default:
				break;
			}
		}
	}
	return 0;
}

/**************************** DRAWING METHOD *******************************/

void CApp::Draw() const{

	SDL_SetRenderDrawColor(m_pRenderer,
			APP_WINDOW_COLOR_BKGND.r,
			APP_WINDOW_COLOR_BKGND.g,
			APP_WINDOW_COLOR_BKGND.b,
			APP_WINDOW_COLOR_BKGND.a);

	SDL_RenderClear(m_pRenderer);

	m_canvas.Draw(m_pRenderer);
	m_toolbox.Draw(m_pRenderer);

    if(mIsBitsSet(m_uStatus, ST_APP_IS_DRAWING)){
        if(m_pSelectedTool->GetType() == TOOL_POLYGON){
        	SDL_SetRenderDrawColor(
                m_pRenderer,
                0,
                200,
                0,
                255);
            SDL_RenderDrawLines(m_pRenderer,m_pVertexes,m_iVertexesNumber);
            SDL_RenderDrawLine(
                m_pRenderer,
                m_pVertexes[m_iVertexesNumber-1].x, m_pVertexes[m_iVertexesNumber-1].y,
                m_ptEnd.x,m_ptEnd.y);

        }
        else{
            SDL_SetRenderDrawColor(
                m_pRenderer,
                m_SelectedColor.r + 100,
				m_SelectedColor.g + 100,
				m_SelectedColor.b + 100,
				m_SelectedColor.a);

            static SDL_Rect Rect;
            Rect = SDL_Rect{m_ptStart.x,m_ptStart.y, m_ptEnd.x-m_ptStart.x, m_ptEnd.y-m_ptStart.y};
            SDL_RenderDrawRect(m_pRenderer, &Rect);
        }
    }
    SDL_RenderPresent(m_pRenderer);
}


SDL_Point CApp::SetRightWay(SDL_Point Start,SDL_Point End){

	if(Start.x > End.x && Start.y > End.y)	return End;
	if(Start.x > End.x && Start.y < End.y ) return SDL_Point{End.x,Start.y};
	if(Start.x < End.x && Start.y > End.y )	return SDL_Point{Start.x,End.y};
	return Start;
}

/************************* CALL BACK FUNCTION  ******************************/

Uint32 _AppTimerCallback(Uint32 interval, void* pParam){
    SDL_Event event;
    event.type=SDL_APP_CALLBACK_EVENT;
    SDL_PushEvent(&event);
    return interval;
}






