
#pragma once

template<typename T>
class InputBuffer {
public:
    InputBuffer(int totalSize, int windowSize);
    ~InputBuffer();
    
    void push_front(const T& item);
    unsigned long size() const;
    
    const T* data() const;

private:
    T* mBuffer;
    int mTotalSize;
    int mWindowSize;
    
    int mFront;
};

template<typename T>
InputBuffer<T>::InputBuffer(int totalSize, int windowSize)
:mTotalSize(totalSize), mWindowSize(windowSize), mFront(totalSize)
{
    mBuffer = new T[mTotalSize];
}

template<typename T>
InputBuffer<T>::~InputBuffer() {
    delete[] mBuffer;
}

template<typename T>
void InputBuffer<T>::push_front(const T& item) {
    if (mFront == 0) {
        mFront = mTotalSize - mWindowSize;
        memcpy(mBuffer + mFront, mBuffer, mWindowSize);
    }
    
    mBuffer[--mFront] = item;
}

template<typename T>
unsigned long InputBuffer<T>::size() const {
    return std::min(mTotalSize - mFront, mWindowSize);
}

template<typename T>
const T* InputBuffer<T>::data() const {
    return mBuffer + mFront;
}
