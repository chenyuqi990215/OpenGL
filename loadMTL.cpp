void Model::loadMTL()
{
    fstream input(MTLName.c_str());
    string s;
    string temp="";
    Material material;
    string texture="";
    bool first;
    string op;
    while (getline(input,s))
    {
        stringstream ss(s);
        ss>>op;
        if (op=="newmtl")
        {
            if (!first)
            {
                MTLinfo[temp]=make_pair(material,texture);
                texture="";
            }
            else
            {
                first=false;
            }
            ss>>temp;
        }
        if (op=="Ns")
            ss>>material.ns;
        if (op=="Ka")
            ss>>material.ka[0]>>material.ka[1]>>material.ka[2];
        if (op=="Kd")
            ss>>material.kd[0]>>material.kd[1]>>material.kd[2];
        if (op=="Ks")
            ss>>material.ks[0]>>material.ks[1]>>material.ks[2];
        if (op=="Ke")
            ss>>material.ke[0]>>material.ke[1]>>material.ke[2];
        if (op=="Ni")
            ss>>material.ni;
        if (op=="map_Kd" || op=="map_Bump")
        {
            string tempTexture;
            ss>>tempTexture;
            for (int i=0;i<tempTexture.length();i++)
                if (tempTexture[i]='/')
                    tempTexture[i]=' ';    //adjust to relative path
            stringstream tt(tempTexture);
            while (tt>>texture);
        }
    }
}
