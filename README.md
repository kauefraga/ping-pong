<div align="center">
  <h1><code>Ping Pong</code></h1>

  <p>
    <strong>🏓 The classic ping pong game made with Raylib/C++. 🏓</strong>
  </p>

  <p>
    <img
      alt="GitHub top language"
      src="https://img.shields.io/github/languages/top/kauefraga/ping-pong"
    />
    <img
      alt="GitHub all releases"
      src="https://img.shields.io/github/downloads/kauefraga/ping-pong/total"
    />
    <a href="https://github.com/kauefraga/ping-pong/commits/main">
      <img
        alt="GitHub last commit"
        src="https://img.shields.io/github/last-commit/kauefraga/ping-pong"
      />
    </a>
    <img
      alt="GitHub LICENSE"
      src="https://img.shields.io/github/license/kauefraga/ping-pong"
    />
  </p>
</div>

### Features (v2.1.0)

- A classic game with all the implementations you would expect.
- Player versus Computer (simple AI algorithm).
- Player versus Player (ws and arrows).
- A ball that moves faster than your reflex.
- A dead-simple score implementation.
- It's written in C++, so it's blazingly fast!
- It's very lightweight. It is consuming around 25MB of RAM!!

## ⬇️ Getting Started

### How to install and run it

1. Install the game executable in the [releases section](https://github.com/kauefraga/ping-pong/releases);
2. Unzip it inside the folder and keep the files as they are;
3. Double click the `ping-pong.exe` and enjoy the gameplay!

Feel free to open an [issue](https://github.com/kauefraga/ping-pong/issues). We'd like to read and fix the bugs you spotted!

### How to play

Currently, it's pretty straightforward:

- When you execute the game you are going to see the logo scene
  - press <kbd>spacebar</kbd>
- Sequentially, you're gonna see the game mode selector
  - press <kbd>w</kbd> or <kbd>arrow up</kbd> to select Player versus CPU
  - press <kbd>s</kbd> or <kbd>arrow down</kbd> to select Player versus Player
  - then hit <kbd>enter</kbd> to proceed
- In the gameplay scene you will see the ping pong court
  - press <kbd>w</kbd> or <kbd>s</kbd> to move the player one (left)
  - press <kbd>arrow up</kbd> or <kbd>arrow down</kbd> to move the player two (right), if they exist

You learned how to play Ping Pong! Hope you like it 💙

## 💖 Collaborators

See who helped to make this project better, [CREDITS](CREDITS.md).

## 📑 Roadmap

A list to keep track of what's coming soon.

- [ ] Release version 2.2.0.
  - [x] Add background sound track.
  - [x] Fix ball table collision sound.
  - [ ] Implement `winner` (after 25 points).
  - [ ] Implement window resizing.
  - [ ] Implement a settings menu (subscene of gameplay scene)
- [ ] Refactor
  - Solve scene management

## 📝 License

This project is licensed under the GPL-3.0 License - See the [LICENSE](https://github.com/kauefraga/ping-pong/blob/main/LICENSE) for more information.
