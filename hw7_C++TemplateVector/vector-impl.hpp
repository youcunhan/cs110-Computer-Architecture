namespace __detail
{
    // Iterator of vector
    template <typename _Tp>
    class __iterator
    {
        public:
            _Tp* pointer;
            __iterator();                                           // Default constructor
            __iterator(const __iterator<_Tp> &other);               // Copy constructor
            __iterator(_Tp *ptr);                                   // Initialize the iterator with a pointer
            ~__iterator();                                          // Destructor
            __iterator<_Tp>& operator=(const __iterator<_Tp> &that);// copy assignment operator
            _Tp& operator*() const;                                 // dereference operator
            _Tp* operator->();                                      // arrow operator
            bool operator==(const __iterator<_Tp> &that);           // comparison operator==
            bool operator!=(const __iterator<_Tp> &that);           // comparison operator!=
            __iterator<_Tp>& operator++();                          // self increment operator ++i
            __iterator<_Tp>& operator--();                          // self decrement operator --i
            __iterator<_Tp> operator++(int);                        // self increment operator i++
            __iterator<_Tp> operator--(int);                        // self decrement operator i--
            __iterator<_Tp> operator+(int n);                       // arithmetic operator+
            __iterator<_Tp> operator-(int n);                       // arithmetic operator-
            __iterator<_Tp>& operator+=(int n);                     // compound assignment operator+=
            __iterator<_Tp>& operator-=(int n);                     // compound assignment operator-=
    };

    template <typename _Tp>
    __iterator<_Tp>::__iterator(){
        pointer = nullptr;//Dummy assignment
    }

    template <typename _Tp>
    __iterator<_Tp>::__iterator(const __iterator<_Tp> &other){
        this->pointer = other.pointer;//copy the pointer
    }

    template <typename _Tp>
    __iterator<_Tp>::__iterator(_Tp *ptr){
        this->pointer = ptr;//assign the ptr
    }

    template <typename _Tp>
    __iterator<_Tp>::~__iterator(){
        //nothing to free
    }

    template <typename _Tp>
    __iterator<_Tp>& __iterator<_Tp>::operator=(const __iterator<_Tp> &that){
        this->pointer = that.pointer;//assign
        return *this;
    }

    template <typename _Tp>
    _Tp& __iterator<_Tp>::operator*() const{
        return *(this->pointer);//get the data
    }

    template <typename _Tp>
    _Tp* __iterator<_Tp>::operator->(){
        return this->pointer;//get the data
    }

    template <typename _Tp>
    bool __iterator<_Tp>::operator==(const __iterator<_Tp> &that){
        return this->pointer == that.pointer;//judge if ptr equals
    }

    template <typename _Tp>
    bool __iterator<_Tp>::operator!=(const __iterator<_Tp> &that){
        return this->pointer != that.pointer;//judge if ptr does not equal
    }

    template <typename _Tp>
    __iterator<_Tp>& __iterator<_Tp>::operator++(){
        this->pointer++;//increment
        return *this;
    }

    template <typename _Tp>
    __iterator<_Tp>& __iterator<_Tp>::operator--(){
        this->pointer--;//decrement
        return *this;
    }

    template <typename _Tp>
    __iterator<_Tp> __iterator<_Tp>::operator++(int){
        __iterator<_Tp> temp = *this;
        this->pointer++;//increment
        return temp;
    }

    template <typename _Tp>
    __iterator<_Tp> __iterator<_Tp>::operator--(int){
        __iterator<_Tp> temp = *this;
        this->pointer--;//decrement
        return temp;
    }

    template <typename _Tp>
    __iterator<_Tp> __iterator<_Tp>::operator+(int n){
        __iterator<_Tp> temp;
        temp.pointer = this->pointer + n;//add
        return temp;
    }

    template <typename _Tp>
    __iterator<_Tp> __iterator<_Tp>::operator-(int n){
        __iterator<_Tp> temp;
        temp.pointer = this->pointer - n;//sub
        return temp;
    }

     template <typename _Tp>
    __iterator<_Tp>& __iterator<_Tp>::operator+=(int n){
        this->pointer += n;//add and assign
        return *this;
    }

     template <typename _Tp>
    __iterator<_Tp>& __iterator<_Tp>::operator-=(int n){
        this->pointer -= n;//sub and assign
        return *this;
    }

    // Const iterator of vector
    template <typename _Tp>
    class __const_iterator
    {
        public:
            _Tp* pointer;
            __const_iterator();                                                  // Default constructor
            __const_iterator(const __const_iterator<_Tp> &other);                // Copy constructor
            __const_iterator(_Tp *ptr);                                          // Initialize the iterator with a pointer
            __const_iterator(const __iterator<_Tp> &other);                      // Convert an iterator into a const iterator
            ~__const_iterator();                                                 // Destructor
            __const_iterator<_Tp>& operator=(const __const_iterator<_Tp> &that); // copy assignment operator
            const _Tp& operator*() const;                                        // dereference operator
            _Tp* operator->();                                                   // arrow operator
            bool operator==(const __const_iterator<_Tp> &that);                  // comparison operator==
            bool operator!=(const __const_iterator<_Tp> &that);                  // comparison operator!=
            __const_iterator<_Tp>& operator++();                                 // self increment operator ++i
            __const_iterator<_Tp>& operator--();                                 // self decrement operator --i
            __const_iterator<_Tp> operator++(int);                               // self increment operator i++
            __const_iterator<_Tp> operator--(int);                               // self decrement operator i--
            __const_iterator<_Tp> operator+(int n);                              // arithmetic operator+
            __const_iterator<_Tp> operator-(int n);                              // arithmetic operator-
            __const_iterator<_Tp>& operator+=(int n);                            // compound assignment operator+=
            __const_iterator<_Tp>& operator-=(int n);                            // compound assignment operator-=
    };

    //most of the function is same as iter
    template <typename _Tp>
    __const_iterator<_Tp>::__const_iterator(){
        pointer = nullptr;
    }

    template <typename _Tp>
    __const_iterator<_Tp>::__const_iterator(const __const_iterator<_Tp> &other){
        this->pointer = other.pointer;
    }

    template <typename _Tp>
    __const_iterator<_Tp>::__const_iterator(_Tp *ptr){
        this->pointer = ptr;
    }

    template <typename _Tp>
    __const_iterator<_Tp>::__const_iterator(const __iterator<_Tp> &other){
        this->pointer = other.pointer;
    }

    template <typename _Tp>
    __const_iterator<_Tp>::~__const_iterator(){

    }

    template <typename _Tp>
    __const_iterator<_Tp>& __const_iterator<_Tp>::operator=(const __const_iterator<_Tp> &that){
        this->pointer = that.pointer;
        return *this;
    }

    template <typename _Tp>
    const _Tp& __const_iterator<_Tp>::operator*() const{
        return *(this->pointer);
    }

    template <typename _Tp>
    _Tp* __const_iterator<_Tp>::operator->(){
        return this->pointer;
    }

    template <typename _Tp>
    bool __const_iterator<_Tp>::operator==(const __const_iterator<_Tp> &that){
        return this->pointer == that.pointer;
    }

    template <typename _Tp>
    bool __const_iterator<_Tp>::operator!=(const __const_iterator<_Tp> &that){
        return this->pointer != that.pointer;
    }

    template <typename _Tp>
    __const_iterator<_Tp>& __const_iterator<_Tp>::operator++(){
        this->pointer++;
        return *this;
    }

    template <typename _Tp>
    __const_iterator<_Tp>& __const_iterator<_Tp>::operator--(){
        this->pointer--;
        return *this;
    }

    template <typename _Tp>
    __const_iterator<_Tp> __const_iterator<_Tp>::operator++(int){
        __const_iterator<_Tp> temp = *this;
        this->pointer++;
        return temp;
    }

    template <typename _Tp>
    __const_iterator<_Tp> __const_iterator<_Tp>::operator--(int){
        __const_iterator<_Tp> temp = *this;
        this->pointer--;
        return temp;
    }

    template <typename _Tp>
    __const_iterator<_Tp> __const_iterator<_Tp>::operator+(int n){
        __const_iterator<_Tp> temp;
        temp.pointer = this->pointer + n;
        return temp;
    }

    template <typename _Tp>
    __const_iterator<_Tp> __const_iterator<_Tp>::operator-(int n){
        __const_iterator<_Tp> temp;
        temp.pointer = this->pointer - n;
        return temp;
    }

     template <typename _Tp>
    __const_iterator<_Tp>& __const_iterator<_Tp>::operator+=(int n){
        this->pointer += n;
        return *this;
    }

     template <typename _Tp>
    __const_iterator<_Tp>& __const_iterator<_Tp>::operator-=(int n){
        this->pointer -= n;
        return *this;
    }
}

//vector implemention
//vector implemention
//vector implemention
//vector implemention
//vector implemention
//vector implemention
//vector implemention

template <typename _Tp>
vector<_Tp>::vector(){
    this->_M_data = new _Tp[2];//take 2 as basic capacity
    this->_M_size = 0;
    this->_M_capacity = 2;
}

template <typename _Tp>
vector<_Tp>::vector(size_type size, const _Tp &value){
    this->_M_size = size;
    this->_M_capacity = size>2? size:2;
    this->_M_data = new _Tp[size];
    for(size_t i=0;i<size;i++)
        this->_M_data[i] = value;
}

template <typename _Tp>
vector<_Tp>::vector(std::initializer_list<_Tp> l){
    this->_M_size = l.size();
    this->_M_capacity = l.size();
    this->_M_data = new _Tp[l.size()];
    size_t t = 0;
    for(_Tp i:l){
        this->_M_data[t] = i;
        t++;
    }
}

template <typename _Tp>
vector<_Tp>::~vector(){
    delete[] this->_M_data;//free all memory
}

template <typename _Tp>
_Tp& vector<_Tp>::operator[](size_t n){
    //if(n >= _M_size);
    return _M_data[n];
}

template <typename _Tp>
size_t vector<_Tp>::size() const{
    return _M_size;
}

template <typename _Tp>
__detail::__iterator<_Tp> vector<_Tp>::begin(){
    __detail::__iterator<_Tp> iter(_M_data);
    return iter;
}

template <typename _Tp>
__detail::__iterator<_Tp> vector<_Tp>::end(){
    __detail::__iterator<_Tp> iter(_M_data + _M_size);
    return iter;
}

template <typename _Tp>
__detail::__const_iterator<_Tp> vector<_Tp>::cbegin() const{
    __detail::__const_iterator<_Tp> citer(_M_data);
    return citer;
}

template <typename _Tp>
__detail::__const_iterator<_Tp> vector<_Tp>::cend() const{
    __detail::__const_iterator<_Tp> citer(_M_data + _M_size);
    return citer;
}

template <typename _Tp>
__detail::__iterator<_Tp> vector<_Tp>::insert(__detail::__iterator<_Tp> pos, const _Tp &value){
    int n = pos.pointer - this->_M_data;
    if(_M_size == _M_capacity) _grow();
    pos.pointer = this->_M_data + n;
    for(_Tp* i=_M_data+_M_size-1;i>=pos.pointer;i--)
        *(i+1) = *i;//move right
    *(pos.pointer) = value;
    _M_size++;
    return pos;
}

template <typename _Tp>
__detail::__iterator<_Tp> vector<_Tp>::insert(__detail::__const_iterator<_Tp> pos, const _Tp &value){
    int n = pos.pointer - this->_M_data;
    if(_M_size == _M_capacity) _grow();
    pos.pointer = this->_M_data + n;
    for(_Tp* i=_M_data+_M_size-1;i>=pos.pointer;i--)
        *(i+1) = *i;//move right
    *(pos.pointer) = value;
    _M_size++;
    __detail::__iterator<_Tp> temp;
    temp.pointer = pos.pointer;
    return temp;
}

template <typename _Tp>
void vector<_Tp>::push_back(const _Tp &value){
    if(_M_size == _M_capacity) _grow();
    _M_data[_M_size] = value;
    _M_size++;
}

template <typename _Tp>
__detail::__iterator<_Tp> vector<_Tp>::erase(__detail::__iterator<_Tp> pos){
    for(_Tp* i=pos.pointer;i!=_M_data+_M_size-1;i++)
        *i = *(i+1);//move left
    _M_size--;
    return pos;
}

template <typename _Tp>
__detail::__iterator<_Tp> vector<_Tp>::erase(__detail::__const_iterator<_Tp> pos){
    for(_Tp* i=pos.pointer;i!=_M_data+_M_size-1;i++)
        *i = *(i+1);//move left
    _M_size--;
    __detail::__iterator<_Tp> temp;
    temp.pointer = pos.pointer;
    return temp;
}

template <typename _Tp>
void vector<_Tp>::pop_back(){
    _M_size--;
}

template <typename _Tp>
void vector<_Tp>::_grow(){
    _Tp* temp = new _Tp[_M_size];
    for(size_t i=0;i<_M_size;i++)
        temp[i] = _M_data[i];
    delete[] _M_data;
    _M_capacity *= 2;
    _M_data = new _Tp[_M_capacity];
    for(size_t i=0;i<_M_size;i++)
        _M_data[i] = temp[i];
    delete[] temp;
}