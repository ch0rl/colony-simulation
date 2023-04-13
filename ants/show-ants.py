"""A Simple Minesweeper Game, with cheats"""

# Imports
import pygame
from dataclasses import dataclass
from typing import Tuple, List

@dataclass
class Point:
    x: int
    y: int
    
@dataclass
class Grid_Item:
    food_amount: int
    pheromone_level: int

# General options
FPS = 6
WIDTH = 100
HEIGHT = 100
INIT_SIZE = (WIDTH, HEIGHT)
PAD = 2
SQUARE_WIDTH = 5
ANT_N = 30

# Colours
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
RED   = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE  = (0, 0, 255)
GREY  = (169, 169, 169)
DARK_GREY = (128,128,128)

def get_rect(pos: Point, width: int, pad: int) -> Tuple[int, int, int, int]:
    return (
        pos.x * width + pad, pos.y * width + pad, width - pad, width - pad
    )

# Setup
pygame.init()

# Clock
CLOCK = pygame.time.Clock()
# Screen
screen = pygame.display.set_mode((WIDTH * SQUARE_WIDTH, HEIGHT * SQUARE_WIDTH))

DATA_FILE = open("map-state")
MAP: List[List[Grid_Item]] = [
    [Grid_Item(0, 0) for _ in range(HEIGHT)] for _ in range(WIDTH)
]
ANTS: List[Point] = [Point(0, 0) for _ in range(ANT_N)]

# Main Game Loop
RUNNING = True
go = False
while RUNNING:
    # Check events
    for event in pygame.event.get():
        match event.type:
            case pygame.QUIT | pygame.WINDOWCLOSE:
                RUNNING = False
            case pygame.KEYDOWN:
                if event.key == pygame.K_SPACE:
                    go = True
                
    if not go: continue
                
    # Load next tick frame
    DATA_FILE.readline()  # Consume tick line
    
    # Map state
    for x in range(WIDTH):
        for y, item in enumerate(DATA_FILE.readline().replace("\n", "").split(" ")[:-1]):
            MAP[x][y].pheromone_level, MAP[x][y].food_amount = map(int, item.split(","))
           
    # Ant state 
    for i, item in enumerate(DATA_FILE.readline().replace("\n", "").split(" ")[:-1]):
        ANTS[i].x, ANTS[i].y = map(int, item.split(","))

    # Set background
    screen.fill(GREY)

    # Draw boxes
    for x in range(WIDTH):
        for y in range(HEIGHT):
            square = MAP[x][y]

            if square.food_amount > 0:
                colour = GREEN
            elif square.pheromone_level > 0:
                colour = DARK_GREY
            else:
                colour = GREY

            pygame.draw.rect(
                screen, colour, get_rect(Point(x, y), SQUARE_WIDTH, PAD)
            )
            
    for ant in ANTS:
        pygame.draw.rect(
            screen, BLACK, get_rect(ant, SQUARE_WIDTH, PAD)
        )

    # Update
    pygame.display.flip()
    CLOCK.tick(FPS)
    
# Finish up
DATA_FILE.close()
