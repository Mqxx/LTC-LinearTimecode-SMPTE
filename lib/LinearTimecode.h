/*
  LinearTimecode.h - Library for decoding linear timecodes send over audio.
*/

#ifndef LinearTimecode_h
#define LinearTimecode_h

class LinearTimecode {
    private:
        
        // default frame sync pattern
        word _frameSyncPattern;
        
        // all timecode digits (H, H, m, m, s, s, f, f)
        volatile int _digits[8];
        
        // frame buffers
        volatile uint8_t _frameBuffers[10];
        
        // framerate and bitlength
        float _framerate;
        unsigned int _bitLength;
        
        // timing
        volatile uint32_t _timeLast;
        volatile uint32_t _timeDifference;
        
        // set if half edge is detected
        bool _halfEdge;
        
        // short edge duration
        unsigned int _shortEdgeDurationMin;
        unsigned int _shortEdgeDurationMax;
        
        // long edge duration
        unsigned int _longEdgeDurationMin;
        unsigned int _longEdgeDurationMax;
        
        // times
        volatile int _timeHours;
        volatile int _timeMinutes;
        volatile int _timeSeconds;
        volatile int _timeFrames;
        
        // constructor init function
        void _init(void);
        
        // shift each bit in frameBuffers one to the right
        void _shiftFrameBuffersRight(volatile uint8_t frameBuffers[10]);
        
        // callback function on sync
        void (*_onSync)(void);
        
    public:
        
        // format types
        const enum formats {
            FORMAT_DOT,
            FORMAT_COLON,
            FORMAT_DOT_COLON,
            FORMAT_SPACE
        };
        
        // frame types
        const enum frameTypes {
            FRAME_23_976,
            FRAME_24,
            FRAME_25,
            NO_DROP_FRAME_29_97,
            FRAME_30
        };
        
        // constructor (frameType)
        LinearTimecode::LinearTimecode(frameTypes frameType);
        
        // constructor (frameDuration)
        LinearTimecode::LinearTimecode(const unsigned int frameDuration);
        
        // get the current byte buffer
        uint8_t getByteBuffer(const unsigned int index);
        
        // get the framerate as float
        float getFramerate();
        
        // get the bit length as int
        const int getBitLength();
        
        // get timecode as string with a format
        String getTimecode(formats format);
        
        // get the frames as int
        const int getFrames();
        
        // get the seconds as int
        const int getSeconds();
        
        // get the minutes as int
        const int getMinutes();
        
        // get the hours as int
        const int getHours();
        
        // set the sync pattern
        void setSyncPattern(const word pattern);
        
        // set short edge duration
        void setShortEdgeDuration(const unsigned int min, const unsigned int max);
        
        // set long edge duration
        void setLongEdgeDuration(const unsigned int min, const unsigned int max);
        
        // call on interrupt change
        void onEdgeChange();
        
        // gets called on synced pattern
        void onSync(void (*callback)(void));
};

#endif


