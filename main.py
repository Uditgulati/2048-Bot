import os
import subprocess
import math

import errno
import pygame
from pygame.locals import *
import copy
from appdirs import user_data_dir

try:
    from game import Game2048
    from manager import GameManager
except ImportError:
    from .game import Game2048
    from .manager import GameManager

def convert(grid):
    var = ""
    for row in grid:
        for tile in row:
            temp = 0
            if tile != 0:
                temp = int(math.log2(int(tile)))

            temp = str(temp)
            if len(temp) == 1:
                temp = '0' + temp

            var += temp
    return var

def run_game(game_class=Game2048, title='2048', data_dir=None):
    pygame.init()
    pygame.display.set_caption(title)

    # Try to set the game icon.
    try:
        pygame.display.set_icon(game_class.icon(32))
    except pygame.error:
        # On windows, this can fail, so use GDI to draw then.
        print('Consider getting a newer card or drivers.')
        os.environ['SDL_VIDEODRIVER'] = 'windib'

    if data_dir is None:
        data_dir = user_data_dir(appauthor='Quantum', appname='2048', roaming=True)
        try:
            os.makedirs(data_dir)
        except OSError as e:
            if e.errno != errno.EEXIST:
                raise

    screen = pygame.display.set_mode((game_class.WIDTH, game_class.HEIGHT))
    manager = GameManager(Game2048, screen,
                          os.path.join(data_dir, '2048.score'),
                          os.path.join(data_dir, '2048.%d.state'))
    mv = None
    oldBoard = copy.deepcopy(manager.game.grid)
    iniFlag = False
    try:
        while True:
            if iniFlag:
                oldBoard = copy.deepcopy(manager.game.grid)
                print("hello")
                convGrid = convert(manager.game.grid)
                process = subprocess.Popen(['./a.out', convGrid], stdout=subprocess.PIPE)
                print(convGrid)
                stdout = process.communicate()[0]
                mv = stdout[len(stdout) - 2] - 48
                print("move {}".format(mv))
                #mv = getMove(convGrid)
                eve = pygame.event.Event(pygame.locals.KEYDOWN)
                if mv == 0:
                    eve.key = K_LEFT
                elif mv == 1:
                    eve.key = K_RIGHT
                elif mv == 2:
                    eve.key = K_UP
                elif mv == 3:
                    eve.key = K_DOWN
                else:
                    eve.key = K_LEFT
                pygame.event.post(eve)

            event = pygame.event.wait()
            manager.dispatch(event)
            for event in pygame.event.get():
                manager.dispatch(event)
            manager.draw()
            if oldBoard != manager.game.grid:
                iniFlag = True
    finally:
        pygame.quit()
        manager.close()


if __name__ == '__main__':
    run_game()
