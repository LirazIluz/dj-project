#ifndef WAVTRACK_H
#define WAVTRACK_H

#include "AudioTrack.h"

/**
 * WAVTrack - Represents a WAV audio file with high-quality uncompressed audio
 * WAV files store raw audio data without compression, providing maximum quality
 * 
 * Contracts:
 * - load(): simulate deck preparation for WAV (often faster due to no decompression).
 * - analyze_beatgrid(): run immediately after load(); can be more precise.
 * - get_quality_score(): derived from sample_rate and bit_depth (higher => better).
 * - clone(): return a deep polymorphic copy used by the mixer; source remains unchanged.
 * - get_quality_score(): function of sample_rate and bit_depth (both higher -> better).
 */
class WAVTrack : public AudioTrack {
private:
    int sample_rate;    // Samples per second: 44100 (CD), 48000 (pro), 96000+ (hi-res)
    int bit_depth;      // Bits per sample: 16 (CD), 24 (pro), 32 (float)

public:
    /**
     * Constructor for WAVTrack
     */
    WAVTrack(const std::string& title, const std::vector<std::string>& artists, 
             int duration, int bpm, int sample_rate, int bit_depth);


    /** Simulates loading a WAV file */
    void load() override;

    /** Simulates beat grid analysis */
    void analyze_beatgrid() override;

    /** Quality score based on sample rate and bit depth */
    double get_quality_score() const override;

    /** Returns a deep copy of this track */
    PointerWrapper<AudioTrack> clone() const override;

    // Getters
    int get_sample_rate() const { return sample_rate; }
    int get_bit_depth() const { return bit_depth; }
};

#endif // WAVTRACK_H