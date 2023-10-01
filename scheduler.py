import sys
import heapq
from collections import deque

class Process:
    def __init__(self, name, arrival_time, burst_time):
        self.name = name
        self.arrival_time = arrival_time
        self.burst_time = burst_time
        self.remaining_time = burst_time
        self.start_time = -1
        self.finish_time = -1

    def __lt__(self, other):
        # Compare processes based on remaining time (SJF)
        return self.remaining_time < other.remaining_time
    
def process_sort(p):
    return p.arrival_time

def preemptive_shortest_job_first(processes, run_for, output_file):
    current_time = 0
    event_queue = []  # Priority queue for events (process switches)
    completed_processes = []

    output_file = open(output_file, "w")  # Open the output file for writing
    sys.stdout = output_file  # Redirect standard output to the output file

    print(f"{len(processes)} processes")
    print("Using preemptive Shortest Job First")

    while current_time < run_for or event_queue:
        # Check for newly arrived processes
        while processes and processes[0].arrival_time <= current_time:
            process = processes.pop(0)
            heapq.heappush(event_queue, (process.remaining_time, process))
            print(f"Time {current_time:4}: {process.name} arrived")

        if event_queue:
            # Get the process with the shortest remaining time
            remaining_time, current_process = heapq.heappop(event_queue)
            execution_time = min(remaining_time, 1)  # Execute for 1 time unit or less

            if current_process.start_time == -1:
                current_process.start_time = current_time
                print(f"Time {current_time:4}: {current_process.name} selected (burst {current_process.burst_time:4})")

            # Update remaining time for the current process
            current_process.remaining_time -= execution_time
            current_time += execution_time

            if current_process.remaining_time == 0:
                current_process.finish_time = current_time
                completed_processes.append(current_process)
                print(f"Time {current_time:4}: {current_process.name} finished at time {current_time}")
            else:
                # Preempt the current process and add it back to the event queue
                heapq.heappush(event_queue, (current_process.remaining_time, current_process))
                print(f"Time {current_time:4}: {current_process.name} preempted (remaining {current_process.remaining_time:4})")

        else:
            # CPU is idle
            print(f"Time {current_time:4}: Idle")
            current_time += 1

    print(f"Finished at time {current_time}\n")

    # Sort completed processes by name before printing the final summary
    completed_processes.sort(key=lambda x: x.name)

    # Calculate and print wait, turnaround, and response times
    for process in completed_processes:
        wait_time = process.start_time - process.arrival_time
        turnaround_time = process.finish_time - process.arrival_time
        response_time = process.start_time - process.arrival_time
        print(f"{process.name} wait {wait_time:4} turnaround {turnaround_time:4} response {response_time:4}")

    # List any unfinished processes in the final summary line
    unfinished_processes = [process.name for process in processes]
    unfinished_processes.sort()  # Sort unfinished processes by name
    if unfinished_processes:
        print("Unfinished processes:", ' '.join(unfinished_processes))

    # Close the output file
    output_file.close()

def round_robin_scheduler(processes, time_slice, run_for, output_file):
    current_time = 0
    event_queue = deque()
    completed_processes = []

    output_buffer = []  # Store output in a list to write to the file later

    output_buffer.append(f"{len(processes)} processes")
    output_buffer.append("Using Round Robin")
    output_buffer.append(f"With Quantum {time_slice}")

    while current_time < run_for or processes or event_queue:
        while processes and processes[0].arrival_time <= current_time:
            process = processes.pop(0)
            event_queue.append(process)
            output_buffer.append(f"Time {current_time:3}: {process.name} arrived")

        if event_queue:
            current_process = event_queue.popleft()
            execution_time = min(current_process.remaining_time, time_slice)
            if current_process.start_time == -1:
              current_process.start_time = current_time

            for _ in range(execution_time):
                output_buffer.append(f"Time {current_time:3}: {current_process.name} selected (burst {current_process.burst_time:4})")
                current_time += 1
                current_process.remaining_time -= 1

                while processes and processes[0].arrival_time <= current_time:
                    process = processes.pop(0)
                    event_queue.append(process)
                    output_buffer.append(f"Time {current_time:3}: {process.name} arrived")

            if current_process.remaining_time > 0:
                event_queue.append(current_process)
                output_buffer.append(f"Time {current_time:3}: {current_process.name} preempted (remaining {current_process.remaining_time})")
            else:
                current_process.finish_time = current_time
                completed_processes.append(current_process)
                output_buffer.append(f"Time {current_time:3}: {current_process.name} finished")

        else:
            output_buffer.append(f"Time {current_time:3}: Idle")
            current_time += 1

    output_buffer.append(f"Finished at time {current_time}\n")

    # Sort completed processes by name before printing
    completed_processes.sort(key=lambda process: process.name)

    for process in completed_processes:
        turnaround_time = process.finish_time - process.arrival_time
        wait_time = turnaround_time - process.burst_time
        response_time = process.start_time - process.arrival_time
        output_buffer.append(f"{process.name} wait {wait_time:3} turnaround {turnaround_time:3} response {response_time:3}")

    # Write the output to the file
    with open(output_file, "w") as f:
        f.write("\n".join(output_buffer))

def first_come_first_serve(processes, run_for, output_file):
    current_time = 0
    completed_processes = []
    unfinished_processes = []

    output_file = open(output_file, "w")  # Open the output file for writing
    sys.stdout = output_file  # Redirect standard output to the output file

    print(f"{len(processes)} processes")
    print("Using First Come First Serve")

    while processes or current_time < run_for:
        if processes and processes[0].arrival_time <= current_time:
            current_process = processes.pop(0)
            if current_process.start_time == -1:
              current_process.start_time = current_time
            execution_time = min(current_process.remaining_time, 1)

            print(f"Time {current_time:4}: {current_process.name} selected (burst {current_process.burst_time:4})")

            current_time += execution_time
            current_process.remaining_time -= execution_time

            if current_process.remaining_time == 0:
                current_process.finish_time = current_time
                completed_processes.append(current_process)
                print(f"Time {current_time:4}: {current_process.name} finished at time {current_time}")
            else:
                # Process hasn't finished; add it back to the queue
                processes.insert(0, current_process)
        else:
            print(f"Time {current_time:4}: Idle")
            current_time += 1

    print(f"Finished at time {current_time}\n")

    # Sort completed processes by name before printing the final summary
    completed_processes.sort(key=lambda x: x.name)

    # Calculate and print wait, turnaround, and response times for completed processes
    for process in completed_processes:
        wait_time = process.start_time - process.arrival_time
        turnaround_time = process.finish_time - process.arrival_time
        response_time = process.start_time - process.arrival_time
        print(f"{process.name} wait {wait_time:4} turnaround {turnaround_time:4} response {response_time:4}")

    # Identify and list any unfinished processes
    for process in processes:
        unfinished_processes.append(process.name)

    # If there are unfinished processes, print them
    if unfinished_processes:
        print("Unfinished processes:", ' '.join(unfinished_processes))

    # Close the output file
    output_file.close()

if __name__ == "__main__":
    if len(sys.argv) != 2:
      print("Invalid arguments. (Usage: process_scheduler.py <filename>.in)")
      exit(1)

    input_file = sys.argv[1]
    if input_file[-3:] != ".in":
      print("Invalid file type. Accepted files are of type '.in'.")
      exit(1)
    
    output_file = (input_file.split(".in")[0]) + ".out"

    # Read process information from the input file
    try:
        with open(input_file, "r") as file:
            lines = file.readlines()
    except FileNotFoundError:
        print(f"Could not find file {input_file}")
        exit(1)

    process_count = None
    run_for = None
    processes = []
    algorithm = None
    time_slice = None

    for line in lines:
        tokens = line.strip().split()
        if tokens[0] == "processcount":
            process_count = int(tokens[1])
        elif tokens[0] == "runfor":
            run_for = int(tokens[1])
        elif tokens[0] == "use":
            algorithm = tokens[1]
        elif tokens[0] == "quantum":
            time_slice = int(tokens[1])
        elif tokens[0] == "process":
            name = None
            arrival_time = None
            burst_time = None
            for i in range(1, len(tokens), 2):
                if tokens[i] == "name":
                    name = tokens[i + 1]
                elif tokens[i] == "arrival":
                    arrival_time = int(tokens[i + 1])
                elif tokens[i] == "burst":
                    burst_time = int(tokens[i + 1])
            if name is not None and arrival_time is not None and burst_time is not None:
                processes.append(Process(name, arrival_time, burst_time))

    processes.sort(key=process_sort)

    if process_count is not None and run_for is not None and len(processes) == process_count and algorithm is not None:
        if algorithm == "sjf":
          preemptive_shortest_job_first(processes, run_for, output_file)
        elif algorithm == "rr" and time_slice is not None:
          round_robin_scheduler(processes, time_slice, run_for, output_file)
        elif algorithm == "fcfs":
            first_come_first_serve(processes, run_for, output_file)
        else:
            print("Invalid algorithm.")
    else:
        print("Invalid input format.")