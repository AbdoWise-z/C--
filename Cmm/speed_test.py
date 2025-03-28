import time

speed = 0.0
eps = 0.8

print("0 it/s", end="")

while True:
    t = int(time.time())  # Get the current second
    it = 0
    while t == int(time.time()):  # Count iterations within the same second
        it += 1

    speed = speed + (it - speed) * eps
    print(f"\r{speed:.2f} it/s", end="", flush=True)
