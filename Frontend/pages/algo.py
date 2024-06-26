import streamlit as st
import pandas as pd
import subprocess
import plotly.graph_objects as go

# Function to read timeline.txt and convert to a 2D vector
def read_timeline_file(filename):
    timeline = []
    with open(filename, 'r') as f:
        for line in f:
            line = line.strip()
            if line:
                row = []
                for char in line:
                    if char == '.':
                        row.append(0)  # Assuming 0 represents empty slot
                    elif char == '*':
                        row.append(1)  # Assuming 1 represents filled slot
                    else:
                        # Handle unexpected characters if needed
                        pass
                timeline.append(row)
    return timeline

# Function to read timeline.txt and convert to a 2D vector
def read_stats(filename):
    stats = []
    with open(filename, 'r') as f:
        for line in f:
            line = line.strip()
            if line:
                row = []
                for val in line:
                    if val!=' ':
                        row.append(int(val))
                stats.append(row)
    return stats

# Create a DataFrame for visualization
def create_timeline_df(timeline):
    data = []
    for process_idx, process_timeline in enumerate(timeline):
        for time_slot, value in enumerate(process_timeline):
            if value == 1:
                data.append({
                    'Process': f'Process {process_idx + 1}',
                    'Start': time_slot,
                    'Finish': time_slot + 1
                })
    return data

def trace(timeline):
    # Generate the timeline DataFrame
    timeline_data = create_timeline_df(timeline)

    # Create a Gantt chart using Plotly
    fig = go.Figure()

    for process in timeline_data:
        fig.add_trace(go.Bar(
            x=[process['Finish'] - process['Start']],
            y=[process['Process']],
            base=[process['Start']],
            orientation='h',
            name=process['Process']
        ))

    # Update the layout of the chart
    fig.update_layout(
        title='CPU Scheduler Timeline',
        xaxis_title='Time',
        yaxis_title='Processes',
        barmode='stack',
        bargap=0.1,
        bargroupgap=0,
        showlegend=False
    )

    # Display the chart in Streamlit
    st.title('CPU Scheduler Visualization')
    st.plotly_chart(fig)
    
# Function to visualize statistics for CPU scheduling
def visualize_statistics(stats):
    # Create a DataFrame from the statistics data
    df = pd.DataFrame(stats, columns=['Arrival Time', 'Burst Time', 'Finish Time', 'Turnaround Time', 'Normalized Turnaround Time'])

    # Create a Plotly figure for statistics visualization
    fig = go.Figure()

    # Add bar chart traces for each statistic
    for i, col in enumerate(df.columns):
        fig.add_trace(go.Bar(
            x=df[col],
            y=df.index + 1,  # Shift indices to start from 1
            orientation='h',
            name=col,
            marker=dict(color=f'rgba({i * 30}, {255 - i * 30}, 100, 0.6)'),  # Adjust color dynamically
            hoverinfo='x'
        ))

    # Update the layout of the chart
    fig.update_layout(
        title='CPU Scheduler Statistics',
        xaxis_title='Duration',
        yaxis_title='Processes',
        yaxis=dict(tickvals=list(range(1, len(df) + 1))),  # Set y-axis ticks to process numbers
        barmode='stack',
        bargap=0.1,
        bargroupgap=0.2,
        showlegend=True,
        legend=dict(x=0.85, y=0.98)
    )

    # Display the chart in Streamlit
    st.title('CPU Scheduler Statistics Visualization')
    st.plotly_chart(fig)
    

# Title of the app
st.title('CPU Scheduler - Select Scheduling Algorithm')

# Check if processes are available
if 'process_list' not in st.session_state or not st.session_state.process_list:
    st.warning("No processes found! Please go back and add processes.")

# Display the list of processes
st.subheader("Processes List")
df = pd.DataFrame(st.session_state.process_list, columns=["Process ID", "Arrival Time", "Burst Time", "Priority"])
st.table(df)

# Dropdown to select the scheduling algorithm
algorithm = st.selectbox("Select an Algorithm", ["Aging", "Feedback", "First-Come First-Served", "Highest Response Ratio Next", "Longest Job First", "Longest Remaining Time", "Priority Scheduling", "Round Robin", "Shortest Job First", "Shortest Remaining Time" ])
mapping={
"Aging":"AGING",
"Feedback":"FEEDBACK",
"First-Come First-Served":"FCFS",
"Highest Response Ratio Next":"HRRN",
"Longest Job First":"LJF",
"Longest Remaining Time":"LRT",
"Priority Scheduling":"PRIORITY",
"Round Robin (Time Quantum - 4)":"RR",
"Shortest Job First":"SJF",
"Shortest Remaining Time":"SRT"
}

# Submit button to finalize the algorithm selection
if st.button("Submit Algorithm"):
    st.session_state.selected_algorithm = algorithm
    # st.experimental_set_query_params(page="algorithm_results")
    st.success(f"Selected Algorithm: {algorithm}")
    with open("algo.txt", 'w') as f:
        f.write(mapping[algorithm])
    
    # Run the C++ program
    result = subprocess.run(['../scheduler'], capture_output=True, text=True)
    timeline=read_timeline_file('timeline.txt')
    trace(timeline)
    stats=read_stats('stats.txt')
    visualize_statistics(stats)
    

# Back button to return to the previous page
if st.button("Back to Process Input"):
    st.switch_page("landing.py")
