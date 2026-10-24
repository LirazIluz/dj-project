# DJ Session Manager (C++)

A C++ simulation of a DJ controller: it loads a music library, plays playlists through an LRU track cache and mixes tracks between two decks with BPM matching. I built it together with two partners in the Systems Programming course at Ben-Gurion University.

The main focus of the project is **manual memory management in C++**: ownership, the Rule of 5, move semantics and a custom smart pointer.

## What we implemented

- **Rule of 5 in `AudioTrack`**: destructor, copy constructor, copy assignment, move constructor and move assignment, with a deep copy of the waveform buffer and safe self-assignment
- **`PointerWrapper<T>`**: a template smart pointer similar to `std::unique_ptr`: move-only (copying is deleted), `operator*`, `operator->`, `release()`, `reset()` and `swap`
- **Polymorphic tracks**: `MP3Track` and `WAVTrack` inherit from the abstract `AudioTrack` and implement `load()`, beat-grid analysis, a quality score and a virtual `clone()`
- **LRU cache**: a fixed-size cache of tracks. Each access updates the slot's access time, and when the cache is full the least recently used track is evicted
- **Mixing engine**: two decks that switch on every load, with automatic BPM sync when the difference is within a configured tolerance
- **Playlist**: a linked list of tracks. We found and fixed the memory leaks in it
- **DJ session**: runs the whole flow (library, cache, decks) and prints statistics: cache hits, misses, evictions, deck loads and errors

## Project structure

```
bin/        dj_config.txt (sample configuration)
include/    header files
src/        source files
Makefile
```

| Component | Responsibility |
|---|---|
| `AudioTrack`, `MP3Track`, `WAVTrack` | Track data and format-specific behavior |
| `PointerWrapper` | Ownership of dynamically allocated tracks |
| `LRUCache`, `CacheSlot` | Track cache with LRU eviction |
| `DJLibraryService` | Builds the track library |
| `DJControllerService` | Loads tracks into the cache |
| `MixingEngineService` | Two decks and BPM sync |
| `Playlist` | Linked list of tracks |
| `SessionFileParser`, `ConfigurationManager` | Reads the configuration file |
| `DJSession` | Runs the session and collects statistics |

## Build and run

```bash
make
./bin/dj_manager -I -A
```

- `-I`: run the interactive DJ session
- `-A`: play all playlists automatically

The session reads its settings (library tracks, playlists, cache size, BPM tolerance, auto sync) from `bin/dj_config.txt`. A sample configuration is included.

## Memory safety

Compiled with `-Wall -Wextra -pedantic -Weffc++` and checked with Valgrind for leaks and invalid memory access:

```bash
make test-leaks
```
