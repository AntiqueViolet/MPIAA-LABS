#pragma once

class Process {
public:
    Process() = default;        
    Process(int start, int finish) :
        start(start), finish(finish) {
    }        

    bool operator<(const Process &a) const;
    bool operator==(const Process &a) const;

public:
    int start {0};
    int finish {0};
};