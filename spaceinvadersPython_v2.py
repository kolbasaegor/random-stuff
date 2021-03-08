from time import sleep
from os import system
from random import randint
import win32api # if it is not imported, enter "pip install pywin32" in the console.
                # This library is used to control the player in real time.

def action(): #function to control the palayer
    if win32api.GetAsyncKeyState(ord('A')) != 0:
        return 'a'
    elif win32api.GetAsyncKeyState(ord('D')) != 0:
        return 'd'
    elif win32api.GetAsyncKeyState(ord('M')) != 0:
        return 'm'
    else:
        return ' '

sizey = 23
sizex = 40
world = [['' for x in range(sizex + 1)] for y in range(sizey+1)] #create world
player = 'A'
playerLaser = '^'
enemy = 'M'
enemyShielded = 'O'
enemyLaser = 'U'
explosion = 'X'

score = 0
victory = 1
laserReady = 1
enemyReady = 0

#welcome screen
print("\n \n     Welcome soldier! \n \n \n \n")
sleep(1)
print("  Brave the COMMAND PROMPT INVADERS and come back a hero. \n \n \n \n")
sleep(1)
print("               Good luck.")
sleep(1)

#initialise world
totalEnemies = 0
for x in range(sizex):
    for y in range(sizey):
        if ((y + 1) % 2 == 0 and y < 7 and x > 4 and x < sizex - 5 and x % 2 == 0): 
            world[y][x] = enemy
            totalEnemies += 1
        elif ((y + 1) % 2 == 0 and y >= 7 and y < 9 and x > 4 and x < sizex - 5 and x % 2 == 0):
            world[y][x] = enemyShielded
            totalEnemies = totalEnemies + 2
        else:
            world[y][x] = ' '
        
world[sizey - 1][sizex // 2] = player
i = 1 #time
direction = 'l'
currentEnemies = totalEnemies

######################   game loop   ######################
while (currentEnemies > 0 and victory):
    drop = 0
    enemySpeed = 1 + 10 * currentEnemies // totalEnemies
    laserReady += 1

    #laser time
    for x in range(sizex):
        for y in range(sizey-1,-1,-1):
            if (i % 2 == 0 and world[y][x] == enemyLaser and (world[y + 1][x] != enemy and world[y + 1][x] != enemyShielded and world[y + 1][x] != playerLaser)):
                world[y + 1][x] = enemyLaser
                world[y][x] = ' '
            elif (i % 2 == 0 and world[y][x] == enemyLaser and (world[y + 1][x] == enemy or world[y + 1][x] == enemyShielded or world[y + 1][x] == playerLaser)):
                world[y][x] = ' '
                if (world[y + 1][x] == playerLaser):
                    world[y+1][x]=' '
            
        
    #player interaction with the world
    for x in range(sizex):
        for y in range(sizey):
            if ((i % 5) == 0 and (world[y][x] == enemyShielded or world[y][x] == enemy) and (randint(0,14)) > 13 and world[y + 1][x] != playerLaser):
                for yi in range(y+1,sizey):
                    if (world[yi][x] == enemy or world[yi][x] == enemyShielded):
                        enemyReady = 0
                        break
                    enemyReady = 1
                if (enemyReady):
                    world[y + 1][x] = enemyLaser
                
            
            if (world[y][x] == playerLaser and world[y - 1][x] == enemy):
                world[y][x] = ' '
                world[y - 1][x] = explosion
                currentEnemies -= 1
                score = score + 50
            elif (world[y][x] == playerLaser and world[y - 1][x] == enemyShielded):
                world[y][x] = ' '
                world[y - 1][x] = enemy
                currentEnemies-= 1
                score = score + 50
            elif (world[y][x] == playerLaser and world[y - 1][x] == enemyLaser):
                world[y][x] = ' '
                world[y - 1][x] = ' '
            elif (world[y][x] == explosion):
                world[y][x] = ' '
            elif ((i + 1) % 2 == 0 and world[y][x] == enemyLaser and world[y + 1][x] == player):
                world[y + 1][x] = explosion
                world[y][x] = ' '
                victory = 0
            elif (world[y][x] == playerLaser and world[y - 1][x] != enemyLaser):
                world[y][x] = ' '
                world[y - 1][x] = playerLaser
            
        
    

    #update enemy direction
    for y in range(sizey):
        if (world[y][0] == enemy):
            direction = 'r'
            drop = 1
            break
        
        if (world[y][sizex - 1] == enemy):
            direction = 'l'
            drop = 1
            break
        
    

    #update board
    if (i % enemySpeed == 0):
        if (direction == 'l'):
            for x in range(sizex - 1):
                for y in range(sizey):
                    if (drop and (world[y - 1][x + 1] == enemy or world[y - 1][x + 1] == enemyShielded)):
                        world[y][x] = world[y - 1][x + 1]
                        world[y - 1][x + 1] = ' '
                    elif (not drop and (world[y][x + 1] == enemy or world[y][x + 1] == enemyShielded)):
                        world[y][x] = world[y][x + 1]
                        world[y][x + 1] = ' '
                    
                
            
        else:
            for x in range(sizex,0,-1):
                for y in range(sizey):
                    if (drop and (world[y - 1][x - 1] == enemy or world[y - 1][x - 1] == enemyShielded)):
                        world[y][x] = world[y - 1][x - 1]
                        world[y - 1][x - 1] = ' '
                    elif (not drop and (world[y][x - 1] == enemy or world[y][x - 1] == enemyShielded)):
                        world[y][x] = world[y][x - 1]
                        world[y][x - 1] = ' '
                    
                
            
        
        for x in range(sizex):
            if (world[sizey - 1][x] == enemy or world[sizey - 1][x] == enemyShielded):
                victory = 0
            
        
    

    #display world
    system("cls")
    print("     SCORE:    ", score)
    for y in range(sizey):
        print("|", end = '')
        for x in range(sizex):
            print(world[y][x],end = '')
        
        print("|")
    
    keyPress = action()

    causedSuicide = 0

    #processing the player's actions
    if (keyPress == 'a'):
        for x in range(sizex - 1):
            if (world[sizey - 1][x + 1] == player):
                if (world[sizey - 1][x] == enemyLaser):
                    causedSuicide = 1
                    break
                
                world[sizey - 1][x] = player
                world[sizey - 1][x + 1] = ' '
            
    if (keyPress == 'd'):
        for x in range(sizex - 1, 0,-1):
            if (world[sizey - 1][x - 1] == player):
                if (world[sizey - 1][x] == enemyLaser):
                    causedSuicide = 1
                    break
                
                world[sizey - 1][x] = player
                world[sizey - 1][x - 1] = ' '

    if (keyPress == 'm' and laserReady > 2):
        for x in range(sizex):
            if (world[sizey - 1][x] == player):
                world[sizey - 2][x] = playerLaser
                laserReady = 0
            
        
    
    if (causedSuicide == 1):
        victory = 0
        break
    
    i+= 1 #increase time by 1
    sleep(0.05)

system("cls")
print("     SCORE:    ", score)
for y in range(sizey):
    print("|", end = '')
    for x in range(sizex):
        print(world[y][x], end = '')
    
    print("|",end = '')
    print()

sleep(1)
system("cls")
if (victory != 0):
    print("\n \n \n \n \n \n               CONGRATULATIONS! \n \n \n \n \n")
    sleep(1)
    print("\n \n               Score: ", score)
    sleep(1)
    bonus = totalEnemies * 20 - i
    print("\n \n               Bonus: ", bonus)
    sleep(1)
    print("\n \n               Total Score: ", score + bonus)
    print("\n \n \n \n               Well done", end =' ')
    sleep(1)
    print(", Hero.")
    sleep(1)
else:
    print("\n \n \n \n \n \n               You have failed.")
    sleep(1)
    print("\n \n               Final Score:", score)
    