# Arduino UNO Q Edge Impulse to protect an item with ML
# Executes edge-impulse-linux-runner and parses its output
# DebConf '26 
# Roni Bandini @ronibandini 07/2026 MIT License

import json
import os
import subprocess
import time


RUNNER_PATH = "edge-impulse-linux-runner"

CONFIDENCE_THRESHOLD = 0.65
CONSECUTIVE_MISSES_LIMIT = 5

STARTUP_BANNER = r"""
██████╗ ███████╗██████╗  ██████╗ ██████╗ ███╗   ██╗███████╗██████╗  ██████╗ 
██╔══██╗██╔════╝██╔══██╗██╔════╝██╔═══██╗████╗  ██║██╔════╝╚════██╗██╔════╝ 
██║  ██║█████╗  ██████╔╝██║     ██║   ██║██╔██╗ ██║█████╗   █████╔╝███████╗ 
██║  ██║██╔══╝  ██╔══██╗██║     ██║   ██║██║╚██╗██║██╔══╝  ██╔═══╝ ██╔═══██╗
██████╔╝███████╗██████╔╝╚██████╗╚██████╔╝██║ ╚████║██║     ███████╗╚██████╔╝
╚═════╝ ╚══════╝╚═════╝  ╚═════╝ ╚═════╝ ╚═╝  ╚═══╝╚═╝     ╚══════╝ ╚═════╝
"""

ASCII_BANNER  = r"""
    _    _        _    ____  __  __    _    
   / \  | |      / \  |  _ \|  \/  |  / \   
  / _ \ | |     / _ \ | |_) | |\/| | / _ \  
 / ___ \| |___ / ___ \|  _ <| |  | |/ ___ \ 
/_/   \_\_____/_/   \_\_| \_\_|  |_/_/   \_\
"""

def print_startup_banner() -> None:
    clear_screen()
    print(STARTUP_BANNER)
    print("  Edge ML en Debian con pequeños dispositivos")
    print("  Roni Bandini 23/7/2026")
    print()
    print(f"  Threshold:        {CONFIDENCE_THRESHOLD * 100:.1f}%")
    print(f"  Consecutive miss: {CONSECUTIVE_MISSES_LIMIT}")
    print(f"  Runner:           {RUNNER_PATH}")
    print()
    print("  Starting runner...\n")


def clear_screen() -> None:
    os.system("clear" if os.name == "posix" else "cls")


def parse_bounding_boxes(line: str) -> list[dict] | None:
    if "boundingBoxes" not in line:
        return None

    json_start = line.find("[")

    if json_start == -1:
        return None

    try:
        boxes = json.loads(line[json_start:])
    except json.JSONDecodeError:
        return None

    return boxes if isinstance(boxes, list) else None


def get_watch_confidence(boxes: list[dict]) -> float:
    highest_confidence = 0.0

    for box in boxes:
        if box.get("label") != "arduino":
            continue

        try:
            confidence = float(box.get("value", 0))
        except (TypeError, ValueError):
            continue

        highest_confidence = max(highest_confidence, confidence)

    return highest_confidence


def main() -> None:
    clear_screen()
    print_startup_banner()

    try:
        runner = subprocess.Popen(
            [RUNNER_PATH],
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            text=True,
            bufsize=1,
        )
    except FileNotFoundError:
        print(f"Error: {RUNNER_PATH} was not found.")
        return
    except OSError as error:
        print(f"Could not start runner: {error}")
        return

    consecutive_misses = 0
    alarm_active = False

    try:
        if runner.stdout is None:
            print("Could not read runner output.")
            return

        for line in iter(runner.stdout.readline, ""):
            raw = line.strip()

            if not raw:
                if runner.poll() is not None:
                    break

                time.sleep(0.01)
                continue

            boxes = parse_bounding_boxes(raw)

            if boxes is None:
                continue

            confidence = get_watch_confidence(boxes)

            if confidence >= CONFIDENCE_THRESHOLD:
                print(f"Arduino detected: {confidence * 100:.2f}%")

                consecutive_misses = 0
                alarm_active = False
                continue

            consecutive_misses += 1

            if confidence > 0:
                print(
                    f"Arduino Q below threshold: "
                    f"{confidence * 100:.2f}% "
                    f"({consecutive_misses}/"
                    f"{CONSECUTIVE_MISSES_LIMIT})"
                )
            else:
                print(
                    f"Arduino Q not detected "
                    f"({consecutive_misses}/"
                    f"{CONSECUTIVE_MISSES_LIMIT})"
                )

            if (
                consecutive_misses >= CONSECUTIVE_MISSES_LIMIT
                and not alarm_active
            ):
                print(ASCII_BANNER)
                print(
                    f"Threshold: "
                    f"{CONFIDENCE_THRESHOLD * 100:.1f}%"
                )
                print(f"Consecutive misses: {consecutive_misses}")
                print(time.strftime("Time: %Y-%m-%d %H:%M:%S"))
                print()

                alarm_active = True

    except KeyboardInterrupt:
        print("\nStopping...")

    finally:
        if runner.poll() is None:
            runner.terminate()

            try:
                runner.wait(timeout=3)
            except subprocess.TimeoutExpired:
                runner.kill()

        print("Runner stopped.")


if __name__ == "__main__":
    main()
