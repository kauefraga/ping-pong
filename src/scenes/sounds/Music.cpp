#include "Music.h"


// Keep track of time played to normalize [0.0f..1.0f]
void normalizeMusic(Music& music, float& timePlayed) {
  // Get normalized time played for current music stream
  timePlayed = GetMusicTimePlayed(music) / GetMusicTimeLength(music);

  if (timePlayed > 1.0f) timePlayed = 1.0f;   // Make sure time played is no longer than music
}

void updateMusic(Music& music, bool& pause, float& timePlayed) {
  UpdateMusicStream(music);

  // Pause/Resume music playing
  if (IsKeyPressed(KEY_P)) {
    pause = !pause;

    if (pause) PauseMusicStream(music);
    else ResumeMusicStream(music);
  }

  normalizeMusic(music, timePlayed);
}
