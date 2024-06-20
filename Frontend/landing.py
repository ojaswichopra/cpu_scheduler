import streamlit as st
import pandas as pd
import subprocess

# Initialize session state for storing process information
if 'process_list' not in st.session_state:
    st.session_state.process_list = []

# Title of the app
st.title('CPU Scheduler')

# Input form for adding a process
with st.form("add_process_form"):
    st.subheader("Add a New Process")
    process_id = st.number_input("Process ID",min_value=0)
    arrival_time = st.number_input("Arrival Time", min_value=0)
    burst_time = st.number_input("Burst Time", min_value=1)
    priority = st.number_input("Priority", min_value=0)
    add_process = st.form_submit_button("Add Process")

    if add_process:
        # Append the process to the process list
        st.session_state.process_list.append({
            "Process ID": process_id,
            "Arrival Time": arrival_time,
            "Burst Time": burst_time,
            "Priority": priority
        })
        st.success(f"Process {process_id} added!")

# Display the list of processes added
if st.session_state.process_list:
    st.subheader("Processes List")
    # Create a DataFrame from the process list
    df = pd.DataFrame(st.session_state.process_list)
    st.table(df)

# Submit button to finalize the input
if st.button("Submit"):
    if st.session_state.process_list:
        # Save processes to a text file
        with open('processes.txt', 'w') as f:
            for process in st.session_state.process_list:
                f.write(f"{process['Process ID']},{process['Arrival Time']},{process['Burst Time']},{process['Priority']}\n")
        
        st.switch_page("pages/algo.py")
    else:
        st.warning("No processes to submit!")

# Clear all processes button 
if st.button("Clear All Processes"):
    st.session_state.process_list = []
    st.success("All processes cleared!")
