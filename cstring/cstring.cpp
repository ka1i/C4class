/*
* @Author: Mardan
* @Date:   2019-11-14 14:13:47
* @Last Modified by:   mardan
* @Last Modified time: 2019-11-17 20:01:09
*/

#include <iostream>
using namespace std;

class cstring
{

private:  /*!< The number of characters allocated in data */

    char*    data;    /*!< The ASCII characters that comprise the String */
    size_t length;

public:

    /*! 
     *  @brief Empty cstring Constructor.
     *  @post cstring length is set equal to 0.
     */
    cstring ( ){
        length = 0;
        data   = nullptr;
    };

    /*! 
     *  @brief Single-character cstring Constructor.
     *  @param[in] c A char literal.
     *  @post cstring data equals @a c and cstring length equals 1.
     */
    cstring (char c){
        length = 1;
        data = new char[2];
        data[0] = c;
        data[1] = '\0';
    };

    /*! 
     *  @brief char* cstring Constructor
     *  @param[in] c A char* null-terminated string.
     *  @post cstring length equals @code{.cpp}strlen(c)@endcode.
     *  @post cstring data equals @a c allocated values, except the null-terminator.
     */
    cstring (const char* c){
        if (c) 
        {
            size_t n = 0;
            while (c[n] != '\0') n++;
            length = n;
            data   = new char[n];
            for (size_t j=0; j < n; j++)
                data[j] = c[j];
        } else 
        {
            length = 0;
            data   = new char[0];
        }
    };
    /*! 
     *  @brief Copy cstring Constructor
     *  @param[in] s A cstring instance.
     *  @post This cstring will be identical to cstring @a s.
     */
    cstring (const cstring& s){
        length = s.size();
        data   = new char[length];
        for (size_t j=0; j < length; j++)
            data[j] = s[j];
    };

    /*! 
     *  @brief Default cstring Destructor
     *  @post cstring data is deleted.
     */
    ~cstring ( ){
        delete[] data;
        data = nullptr;
    };

    /*! 
     *  @brief cstring length.
     *  @return Value in cstring @c length.
     */
    size_t size ( ) const{
        return length;
    };

    /*! 
     *  @brief cstring sub part.
     *  @param[in] c A char literal.
     *  @return The index of @a c in cstring, if exists; -1 otherwise.
     */

    cstring substr (size_t begin_position, size_t char_num){
        try{
            if (length >= begin_position && length > begin_position+char_num){
                cstring temp = nullptr;         
                for (size_t index = begin_position;index < (begin_position+char_num);)
                {
                    temp += data[index++];
                }
                temp += '\0';
                return temp;
            } else{
                throw "out_of_range";
            }
        }
        catch (const char* err){
            char temp;
            char &ref = temp;
            std::cout<<err<<std::endl;
            return ref;

        }
    };
    //@{

    /*! 
     *  @brief cstring empty status.
     *  @return bool result.
    */
    bool is_null() const {
        if (length <= 0 || data == nullptr){
            return true;
        }return false;
    };
    //@{


    /*! 
     *  @brief Stream operators.
     *  @param so A stream object.
     *  @param s  A cstring object.

     *  @return Stream object containing cstring content.
     */
    //@}
    friend std::ostream& operator<< (std::ostream& os, const cstring& s) {
        if (s.size() > 0) 
        {
            for (size_t j=0; j < s.size(); j++)
                os << s[j];
        } else os << "";    

        return os;
    };   

    friend std::istream& operator>> (std::istream& is, cstring& s) {
        char* c = new char[1000];
        is >> c;
        s = cstring(c);
        delete[] c;
        
        return is;
    };
    //@{
    /*! 

     *  @brief Access cstring character.
     *  @param j Index value in cstring.
     *  @pre @a j is less than cstring length.
     *  @return character at @a j index of cstring data.
     *  @throw error info "out_of_range"

     */  
    char& operator[] (size_t j) const{
        try{
            if (j >= length || j < 0) throw "out_of_range";//runtime_error("out_of_range");
                return data[j];
        }
        catch (const char* err){
            char temp;
            char &ref = temp;
            std::cout<<err<<std::endl;
            return ref;

        }
    };
    //@}

    /*! 

     *  @brief calc cstring ascll checksum.
     *  @param[in] s A cstring object.
     *  @return cstring total checksum.
     */
    size_t operator()() 
    {
        size_t checksum=0;
        for (size_t i = 0; i < length; i++){
            checksum += data[i];
        }
        return checksum;
    }; 
 
    //@}

    /*! 

     *  @brief get string pintor.
     *  @param[in] s A cstring object.
     *  @return cstring inside pintor
     */
    char* operator* (){
        return data;
    };   
    //@}

    /*! 
     *  @brief Sets cstring value.
     *  @param[in] s A cstring object.
     *  @return A cstring reference to *this.
     *  @post cstring will be equivalent to @a s.
     */
    cstring& operator= (const cstring& s) 
    {
        if(this == &s) return *this;    

        delete[] data;
        length = s.size();
        data   = new char[length];
        for (size_t j=0; j < length; j++)
            data[j] = s[j];
        return *this;
    };

    /*! 
     *  @brief Append to cstring.
     *  @param[in] s A cstring object.
     *  @return A cstring reference to *this.
     *  @post cstring will equal the concatenation of itself with @a s.
     */
    cstring& operator+= (const cstring& s) 
    {
        size_t size = length + s.size();
        char*    str = new char[size];

        for (size_t j=0; j < length; j++)
            str[j] = data[j];

        for (size_t i=0; i < s.size(); i++)
            str[length+i] = s[i];

        delete[] data;
        length = size;
        data   = str;
        return *this;    
    };

    //@{
    /*! 
     *  @brief cstring concatenation (addition).
     *  @param[in] lhs The left-hand operand cstring or cstring convertable.
     *  @param[in] rhs The right-hand operand cstringg or cstring convertable.
     *  @return Copy of a cstring object.
     *  @post The cstring will be the concatenation of @a lhs and @a rhs.
     */

    friend cstring operator+ (const cstring& lhs, const cstring& rhs) 
    {
        return cstring(lhs) += rhs;
    };

    friend cstring operator+ (const cstring& lhs, char rhs) 
    {
        return cstring(lhs) += cstring(rhs);
    };

    friend cstring operator+ (const cstring& lhs, const char* rhs) 
    {
        return cstring(lhs) += cstring(rhs);
    };

    friend cstring operator+ (char lhs, const cstring& rhs) 
    {
        return cstring(lhs) += rhs;
    };
    friend cstring operator+ (const char* lhs, const cstring& rhs) 
    {
        return cstring(lhs) += rhs;
    };
    //@}
};

int main(){
    char buf[1024];
    std::cin >> buf;
    cstring s1(buf);
    std::cin >> buf;
    cstring s2(buf);
    s1[6] = 'A';
    cstring s3 = 'B';
    s3 = (s1 + s2).substr(7, s2.size());
    std::cout << s1 << *s3 << ' ' << s3()<<endl;
    return 0;
}
