#ifndef __PROGRESSBAR_HPP
#define __PROGRESSBAR_HPP

#include <iostream>
#include <stdexcept>

class progressbar {
public:
    progressbar() = default;
    ~progressbar() = default;

    progressbar(progressbar const&) = delete;
    progressbar& operator=(progressbar const&) = delete;
    progressbar(progressbar&&) = delete;
    progressbar& operator=(progressbar&&) = delete;

    inline progressbar(int n);

    inline void reset();
    inline void set_niter(int iter);
    inline void update(const std::string& status = "");

private:
    int progress = 0;
    int n_cycles = 0;
    int last_perc = -1;
};

inline progressbar::progressbar(int n) : n_cycles(n) {}

inline void progressbar::reset() {
    progress = 0;
    last_perc = -1;
}

inline void progressbar::set_niter(int iter) {
    if (iter <= 0) throw std::invalid_argument("progressbar: iterations must be > 0");
    n_cycles = iter;
}

inline void progressbar::update(const std::string& status) {
    if (n_cycles == 0) throw std::runtime_error("progressbar: number of cycles not set");

    int perc = (n_cycles == 1) ? 100 : (progress * 100) / (n_cycles - 1);

    // Redraw whenever percentage changes
    if (perc != last_perc) {
        // \r snaps to start of line, \033[K clears the bar line completely
        std::cerr << "\r\033[K{"; 

        int pos = perc / 2; // 50 characters wide bar
        for (int i = 0; i < 50; ++i) {
            if (i < pos) std::cerr << '#';
            else std::cerr << '-';
        }

        std::cerr << "} " << perc << "%";

        // Print status on the line below
        if (!status.empty()) {
            // Move down, clear line, print status text
            std::cerr << "\n\033[K" << status;
            // \033[1A moves cursor UP 1 line to return to the bar line
            std::cerr << "\033[1A\r";
        }

        std::cerr << std::flush;
        last_perc = perc;
    }

    progress++;

    // On final cycle: move past both the bar line and the status line
    if (progress == n_cycles) {
        if (!status.empty()) {
            std::cerr << "\n\n"; // 1 newline for status line, 1 for next output/prompt
        } else {
            std::cerr << "\n";   // Standard single newline if no status was provided
        }
    }
}

#endif