#!/bin/bash

echo "Press keys to see their sequences (press 'q' to quit)"

while true; do
    read -rsn1 key
    case "$key" in
        $'\x1B')    # ESC sequence
            read -rsn2 -t 0.01 seq
            echo "ESC${seq}"
            ;;
        $'\x1B[A')  # Up arrow
            echo "UP ARROW"
            ;;
        $'\x1B[B')  # Down arrow
            echo "DOWN ARROW"
            ;;
        $'\x1B[C')  # Right arrow
            echo "RIGHT ARROW"
            ;;
        $'\x1B[D')  # Left arrow
            echo "LEFT ARROW"
            ;;
        $'\x0A')    # ENTER key
            echo "ENTER"
            ;;
        q)          # Quit the script
            break
            ;;
        *)
            echo "Key pressed: $key"
            ;;
    esac
done