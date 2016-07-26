
#include "../utilities/globalDefinitions.hpp"


void print(char* ptr) {
  char* temp = ptr;

 assert (strlen(ptr) <=512, "false ");
  cout << " l =" << strlen(temp) << " ";
  while (*temp != '\0' && *temp !='\n') {
    cout << *temp;
    temp++;
  }


}
int main(int argc, char** argv) {

	FILE *fp;
	char label;
	int size = 0;
	int numOfPartition;
	int src, degree, dst,intlabel;
	int numVertices = 0;
	
	string str;
	char *ctemp[2];
	char buf[512];
	char *p_token = NULL;
	char *context = NULL;
  int id = 0;
  int linecounts =0;
  str = GRAP + "." + PART + "." + HUMA + "." + std::to_string((long long)id);
  fp = fopen(str.c_str(), "r");
    
  if (fp == NULL) return -1;

  while (NULL != fgets(buf, sizeof(buf), fp)) {
	  cout<<endl <<"Processing linecounts =" << linecounts++ ;
    vector<vertexid_t> outEdges;
    vector<label_t> outEdgeValues;
    assert (strlen(buf) <=512, "false ");
	cout <<endl << "1"; 
    print (buf);
    
    p_token = strtok(buf, "\n");
    cout <<endl << "2"; 
    print(p_token);
    p_token = strtok(buf, "\t");
	cout <<endl << "3"; 
    print(p_token);
    src = atoi(p_token);
	cout <<endl << "4"; 
    print(p_token);
    //cout << "s: " << src << " "; 
    p_token = strtok(NULL, "\t");
    degree = atoi(p_token);
	cout <<endl << "5"; 
    print(p_token);
	cout << ":: degree=" <<degree << "::";
    size += degree;
    numVertices++;
    
	int c = 0;
	int i = 0;
		
    p_token = strtok(NULL, "\t");
	cout <<endl << "6"; 
    print(p_token);
    while (p_token != NULL) {
	cout <<endl << "**"; 
    print(p_token);	
		if (i % 2 == 0) {
			outEdges.push_back(atoi(p_token));
			cout << "\txxx" << outEdges[outEdges.size()-1] << "xxx\t";
		} else {
				int tv = atoi(p_token);
				label_t label_value = tv;
			outEdgeValues.push_back(tv);
			
			//cout << "\tytytyt" << tv << "tytyty\t";
			cout << "\tyyy" << (int)outEdgeValues[outEdgeValues.size()-1] << "yyy\t";
			//outEdgeValues.push_back(label_value);
			//cout << "\tfff" << (int)outEdgeValues[outEdgeValues.size()-1] << "fff\t";
		}
		i++;
     // ctemp[i++] = p_token;
      p_token = strtok(NULL, "\t");
      
      // you don't have to do this right? you know which vector to push 
      // one vector has only elements whose index is odd, the other, even
      // that eliminate the char[2]
      /*if (i == 2) {
        outEdges.push_back(atoi(ctemp[0]));
        outEdgeValues.push_back(atoi(ctemp[1]));
        i = 0;
      }*/
		c++;
    }
	assert (i == c, " must be");
	assert (c == degree*2, "false variant");
    cout<<endl;
  }
  cout << linecounts <<endl;
  fclose(fp);
  return 1;
    
}


