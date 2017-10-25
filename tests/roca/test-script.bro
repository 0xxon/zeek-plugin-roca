# @TEST-EXEC: bro -C -r $TRACES/vulnerable.pcap %INPUT
# @TEST-EXEC: btest-diff notice.log

redef ROCA::Notify = T;

