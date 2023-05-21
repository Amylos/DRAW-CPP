/*
 * deifnes.h
 *
 *  Created on: 2022
 *      Author: Garnier
 */



#define APP_WINDOW_TITLE				" MIN DRAW C++ "
#define APP_WINDOW_WIDTH				(1500)
#define APP_WINDOW_HEIGHT				(800)
#define APP_WINDOW_PADDING				(50)
#define APP_WINDOW_COLOR_BKGND			(SDL_Color){0,0,0,255}

#define APP_ANIMATE_RATE				(20)

#define APP_TOOLBOX_WIDTH				(100)
#define APP_TOOLBOX_PADDING				(APP_TOOLBOX_WIDTH/4)
#define APP_TOOLBOX_HEIGHT				(APP_WINDOW_HEIGHT)
#define APP_TOOLBOX_COLOR_BACKGROUND	(SDL_Color){150,150,150,255}
#define APP_TOOLBOX_COLOR_HEAD			(SDL_Color){191,170,143}

#define APP_TOOLBOX_HAND_HEIGHT			(40)

#define APP_TOOL_WIDTH					(APP_TOOLBOX_WIDTH/2)
#define APP_TOOL_HEIGHT					(APP_TOOLBOX_WIDTH/2)
#define APP_TOOL_PADDING				(20)
#define APP_TOOL_COLOR					(SDL_Color){255,255,255,255}

#define APP_CANVAS_X					(APP_TOOLBOX_WIDTH)	//APP_TOOLBOX_WIDTH
#define APP_CANVAS_Y					(0)
#define APP_CANVAS_WIDTH				(APP_WINDOW_WIDTH)	//(APP_WINDOW_WIDTH-APP_TOOLBOX_WIDTH)
#define APP_CANVAS_HEIGHT				(APP_WINDOW_HEIGHT)
#define APP_CANVAS_COLOR_BACKGROUND		(SDL_Color){50,50,50,255}

#define SDL_APP_CALLBACK_EVENT			(SDL_USEREVENT +10)

#define APP_TOOLBOX_COLORCHART_FILE		("./Resources/Images/colorchart.png")
#define TOOL_COLORCHART_HEIGHT_RATIO		(3)






/*
 *
 *
 * 	Polymorphisme = Dynamisme + Virtualité + Redéfinition
 *
 * 	Polymorphisme = Même catégorie d'objet mais comportement différent ou forme différente.
 *
 * 	Dynamisme = Pointeur dynamique & objet dynamique.
 *
 *  Virtualité = Résolution dynamique des liens, adresse des méthodes virtuel résolues à l'éxection  !=  résolution statique des liens à la compilation.
 *
 * 	Redéfinition = Réécriture des méthodes virtuels par les classes et les tiers => comportement différent.
 *
 *
 */
