import streamlit as st
import pandas as pd
import subprocess

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
    # Display the output from the C++ program
    st.subheader("Algorithm Output")
    st.text(result.stdout)
    # Display any errors
    st.subheader("Error Output")
    st.text(result.stderr)

# Back button to return to the previous page
if st.button("Back to Process Input"):
    st.switch_page("landing.py")
