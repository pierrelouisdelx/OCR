#ifndef PARAGRAPH_H
#define PARAGRAPH_H

SDL_Surface* paragraph_reco(SDL_Surface* image);
int * mins_maxs(SDL_Surface* image);
SDL_Surface* lines_reco(SDL_Surface* image);
int lines_and_char_storage(SDL_Surface* image);
SDL_Surface* char_reco(SDL_Surface* image);
int char_storage(SDL_Surface* image);
#endif
