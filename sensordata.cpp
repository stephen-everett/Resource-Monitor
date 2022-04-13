#include "sensordata.h"


int getCpuTemp(string cpuTemp[])
{
    string sensors = GetStdoutFromCommand("sensors | grep Core");
    int coreCount = 0;
    string stringHolder;
    bool openBracket = false;
    for (int i = 0; i < sensors.length();i++)
    {
        if (sensors[i] == '(')
        {
            openBracket = true;
        }
        if (openBracket)
        {
            if (sensors[i] == ')')
            {
                openBracket = false;
                cpuTemp[coreCount] = stringHolder;
                coreCount++;
                i = i+1;
                stringHolder = "";
            }
        }
        else
        {
            if (sensors[i]==':')
            {
                stringHolder+=sensors[i];
                i = i+7;
            }
            else
            {
             stringHolder+=sensors[i];
            }
        }
    }
    return coreCount;
}
string GetStdoutFromCommand(string cmd)
{
    string data;
    FILE * stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    cmd.append(" 2>&1");

    stream = popen(cmd.c_str(), "r");
    if (stream) {
      while (!feof(stream))
        if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
      pclose(stream);
    }
    return data;
}
string CpuName()
{
    string cpuLabelRaw = GetStdoutFromCommand("lscpu | grep 'Model name:'");
    bool appending = false;
    string cpuLabel = "";
    for(int i = 0; i < cpuLabelRaw.length(); i++)
    {
        if (cpuLabelRaw[i] == 'I')
        {
            appending = true;
        }
        if (cpuLabelRaw[i] == 'Q')
        {
            appending = false;
            cpuLabel += cpuLabelRaw[i];
        }
        if (appending)
        {
            cpuLabel += cpuLabelRaw[i];
        }
    }
    return cpuLabel;
}
