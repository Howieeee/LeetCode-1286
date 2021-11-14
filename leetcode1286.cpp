class CombinationIterator {
public:
    string str;
    int c = 0;
    int combine_len = 0;
    vector<int> bit_map;// 1,0
    bool has_next = true;
    CombinationIterator(string characters, int combinationLength) {
        str = characters;
        combine_len = combinationLength;
        // = combinationLength;
        
        bit_map.resize(str.size(),0); //初始化
        for(int i=0;i<combinationLength;i++)
            bit_map[i] = 1;
        
        
    }
    /*
         a b c d e f
         1 1 1 0 0 0 -> 1 1 0 1 0 0 -> 1 1 0 0 1 0 -> 1 1 0 0 0 1 
    move 1 0 1 1 0 0 -> 1 0 1 0 1 0 -> 1 0 1 0 0 1 
    move 1 0 0 1 1 0 -> 1 0 0 1 0 1 
    move 1 0 0 0 1 1 
    move 0 1 1 1 0 0 -> 0 1 1 0 0 1
    move 0 1 0 1 1 0 -> 0 1 0 1 0 1
    move 0 1 0 0 1 1 
    move 0 0 1 1 1 0 -> 0 0 1 1 0 1
    move 0 0 1 0 1 1
    move 0 0 0 1 1 1 
         
    */
    string next() {
        string ans;
        for(int i=0;i<bit_map.size();i++){
            if(bit_map[i] == 1){
                ans += str[i];
                //cout << str[i] << " ";
            }
        }
        c++;
        if(combine_len == bit_map.size()){ // C3 取 3
            has_next = false;
        }
        if(combine_len == 1){ //C3 取 1
            if(c == bit_map.size())
                has_next = false;
        }
        
        // for(auto c:bit_map)
        //     cout << c << " ";
        // cout << endl;
        
        //cout  << ans;
        int bit_size = bit_map.size();
        if(bit_map[bit_size-1] == 0){ // ex 1 1 1 0 0
            for(int i=bit_size-1;i>=0;i--){
                if(bit_map[i] == 1){// 1 1 [1] 0 0
                    bit_map[i+1] = 1;
                    bit_map[i] = 0;
                    break;
                }
                
            }
        }else if(bit_map[bit_size-1] == 1){ //  1 0 0 0 1 1
            int count =1; // 0 1 1 
            
            for(int i=bit_size-2;i>=0;i--){//找到 [1] 0 0 0 {1} 1   最右邊的1,且1的右邊=0
                
                
                if(bit_map[i] == 1){ // 0 1 0 0 0 {1} 1
                    if(bit_map[i+1] == 0){// 0 [1] 0 0 0 {1} 1 ,count =2
                        bit_map[i] = 0;
                        bit_map[i+1] = 1; // 0 {0} 1 0 0 1 1

                        for(int j=i+2;j<bit_size;j++){
                            if(count>0){
                                bit_map[j] = 1;
                                count --;
                            }else{
                                bit_map[j] = 0;
                            }
                        }
                        break;
                    }else{//找到1 但右邊不是0
                        count ++;//看找到之前有幾個1
                    }
                    if(count == combine_len)
                        if(combine_len == 1){
                            if(i == bit_size-1)
                                has_next = false;
                        }else
                            has_next = false;
                }
                
            }
            
        }
        
        return ans;
    }
    
    bool hasNext() {
        return has_next;
    }
};

/**
 * Your CombinationIterator object will be instantiated and called as such:
 * CombinationIterator* obj = new CombinationIterator(characters, combinationLength);
 * string param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
