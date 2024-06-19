import streamlit as st
import pandas as pd

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

# Submit button to finalize the algorithm selection
if st.button("Submit Algorithm"):
    st.session_state.selected_algorithm = algorithm
    # st.experimental_set_query_params(page="algorithm_results")
    st.success(f"Selected Algorithm: {algorithm}")

# Back button to return to the previous page
if st.button("Back to Process Input"):
    st.switch_page("landing.py")
