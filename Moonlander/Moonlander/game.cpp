/*************************************************************
 * File: game.cpp
 * Author: Br. Burton
 *
 * Description: Contains the implementations of the
 *  method bodies for the game class.
 *
 * Please DO NOT share this code with other students from
 *  other sections or other semesters. They may not receive
 *  the same code that you are receiving.
 *************************************************************/

#include "game.h"

#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include "ground.h"
#include "lander.h"

/******************************************
 * GAME :: JUST LANDED
 * Did we land successfully?
 ******************************************/
bool Game :: justLanded() const
{
   bool landed = false;
   
   Point platformCenter = ground.getPlatformPosition();
   int width = ground.getPlatformWidth();

   float xDiff = lander.getPoint().getX() - platformCenter.getX();
   float yDiff = lander.getPoint().getY() - platformCenter.getY();

   float margin = width / 2.0;
   
   if (fabs(xDiff) < margin)
   {
      // between edges
      
      if (yDiff < 4 && yDiff >= 0)
      {
         // right above it
         
         if (fabs(lander.getVelocity().getDx()) < 3 && fabs(lander.getVelocity().getDy()) < 3)
         {
            // we're there!
            landed = true;
         }
      }
   }
   
   return landed;
}

/***************************************
 * GAME :: ADVANCE
 * advance the game one unit of time
 ***************************************/
void Game :: advance()
{
	if (rollCredits)
	{
		
	}

	if (!gameStarted && !rollCredits)
	{
		
	}

	if (gameStarted && !rollCredits)
	{
		if (lander.isAlive() && !lander.isLanded())
		{
			// advance the lander
			lander.applyGravity(GRAVITY_AMOUNT);
			lander.advance();

			// check for crash
			if (!ground.isAboveGround(lander.getPoint()))
			{
				lander.setAlive(false);
			}

			// check for just landed
			if (justLanded())
			{
				lander.setLanded(true);
			}
		}
	}
}

/***************************************
 * GAME :: HANDLE INPUT
 * accept input from the user
 ***************************************/
void Game :: handleInput(const Interface & ui)
{
	// if the credits are rolling, don't accept input
	if (rollCredits)
	{
		
	}

	// before the game starts
	if (!gameStarted && !rollCredits)
	{
		if(ui.isDown())
		{
			select.setY(-50);
			select.setX(-100);
		}

		if (ui.isUp())
		{
			select.setY(0);
			select.setX(-100);
		}

		if (select.getY() == 0 && ui.isSpace())
		{
			gameStarted = true;
		}

		if (select.getY() == -50 && ui.isSpace())
		{
			rollCredits = true;
		}

	}

	// if the game has started
	if (gameStarted && !rollCredits)
	{
		if (lander.isLanded() || !lander.isAlive())
		{
			if (ui.isSpace())
			{
				lander.reset();
				ground.generateGround();
			}

			if (ui.isUp())
			{
				lander.reset();
			}
		}

		// while the moon lander is active
		if (lander.isAlive() && !lander.isLanded())
		{

			if (ui.isDown())
			{
				lander.applyThrustBottom();
			}

			if (ui.isLeft())
			{
				lander.applyThrustLeft();
			}

			if (ui.isRight())
			{
				lander.applyThrustRight();
			}
		}
	}
}

/*********************************************
 * GAME :: DRAW
 * Draw everything on the screen
 *********************************************/
void Game :: draw(const Interface & ui)
{
	// Credit roll state
    if (rollCredits)
    {
		static Point credPos(-150, -200);
		drawCredits(credPos);
		credPos.addY(1);
		if (credPos.getY() == 400)
		{
			rollCredits = false;
			credPos.setY(-200);
		}
    }
	
	// pre game state
	if (!gameStarted && !rollCredits)
    {
		drawLargeText(Point(-65, 150), "Moon Lander");

		drawText(Point(-70, 100), "By Max Schuhmacher");

		drawText(Point(-170, 50), "Use the Up and Down arrows to navigate, press Space to select");

		drawLander(select);
		drawLanderFlames(select, true, false, false);

		drawLargeText(Point (-65, 0), "Start");
		drawLargeText(Point(-65, -50), "Credits");
    }
   
	// active game state
	if (gameStarted && !rollCredits)
	{
		if (lander.isLanded() || !lander.isAlive())
		{
			drawText(Point(-65, 150), "UP - Try Again");
			drawText(Point(-65, 120), "Space - New Map");
		}

		// draw the lander every frame
		lander.draw();

		// check if the lander is landed
		if (lander.isLanded())
		{
			drawText(Point(), "You have successfully landed!");
		}

		// check if the lander has crashed
		if (!lander.isAlive())
		{
			drawText(Point(), "You have successfully crashed!");
		}

		// check if the lander can thrust
		if (lander.canThrust())
		{
			drawLanderFlames(lander.getPoint(), ui.isDown(), ui.isLeft(), ui.isRight());
		}

		// display fuel
		Point fuelLocation;
		fuelLocation.setX(topLeft.getX() + 5);
		fuelLocation.setY(topLeft.getY() - 5);

		drawNumber(fuelLocation, lander.getFuel());

		// draw ground
		ground.draw();
	}
}

