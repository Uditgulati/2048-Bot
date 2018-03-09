import os
import tempfile
import time
import pygame


# Accurate timer for platform.
timer = [time.time, time.clock][os.name == 'nt']

# Get the temp file dir.
tempdir = tempfile.gettempdir()
NAME = '2048'

def BOX(surface,rect,color,radius=0.4):
    rect         = pygame.Rect(rect)
    color        = pygame.Color(*color)
    alpha        = color.a
    color.a      = 0
    pos          = rect.topleft
    rect.topleft = 0,0
    rectangle    = pygame.Surface(rect.size,pygame.SRCALPHA)

    circle       = pygame.Surface([min(rect.size)*3]*2,pygame.SRCALPHA)
    pygame.draw.ellipse(circle,(0,0,0),circle.get_rect(),0)
    circle       = pygame.transform.smoothscale(circle,[int(min(rect.size)*radius)]*2)

    radius              = rectangle.blit(circle,(0,0))
    radius.bottomright  = rect.bottomright
    rectangle.blit(circle,radius)
    radius.topright     = rect.topright
    rectangle.blit(circle,radius)
    radius.bottomleft   = rect.bottomleft
    rectangle.blit(circle,radius)

    rectangle.fill((0,0,0),rect.inflate(-radius.w,0))
    rectangle.fill((0,0,0),rect.inflate(0,-radius.h))

    rectangle.fill(color,special_flags=pygame.BLEND_RGBA_MAX)
    rectangle.fill((255,255,255,alpha),special_flags=pygame.BLEND_RGBA_MIN)
    return surface.blit(rectangle,pos)

def center(total, size):
    return (total - size) / 2


def load_font(name, size, cache={}):
    if (name, size) in cache:
        return cache[name, size]
    if name.startswith('SYS:'):
        font = pygame.font.SysFont(name[4:], size)
    else:
        font = pygame.font.Font(name, size)
    cache[name, size] = font
    return font


def write_to_disk(file):
    file.flush()
    os.fsync(file.fileno())
