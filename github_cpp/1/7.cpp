
#ifndef vsl_quick_file_h_
#define vsl_quick_file_h_













#include <vcl_string.h>
#include <vcl_iostream.h>
#include <vcl_cerrno.h>
#include <vsl/vsl_binary_io.h>



template <class T>
inline bool vsl_quick_file_load(T &data,
                                const vcl_string& path,
                                vcl_ostream* errorStream = &vcl_cerr)
{
  vsl_b_ifstream bfs(path);
  if ( !(!bfs))
  {
    vsl_b_read(bfs,data);
    if (!(!bfs))
    {
      
      char dummy;
      vsl_b_read(bfs,dummy);
      if (bfs.is().eof())
      {
        bfs.close();
        if (errorStream)
          *errorStream << "Successfully loaded: " << path << '\n';
        return true;
      }
    }
  }
  bfs.close();
  if (errorStream)
    *errorStream << "Unable to load: "<< path <<'\n';
  return false;
}



template <class T>
inline bool vsl_quick_file_save(const T &data,
                                const vcl_string& path,
                                vcl_ostream* errorStream = &vcl_cerr)
{
  vsl_b_ofstream bfs(path);
  if (!(!bfs))
  {
    vsl_b_write(bfs,data);
    if (!(!bfs))
    {
      bfs.close();
      if (errorStream)
        *errorStream << "Successfully saved: "<< path <<'\n';
      return true;
    }
  }
  bfs.close();
  if (errorStream)
    *errorStream << "Unable to save: " << path << '\n';
  return false;
}


template <class T, class S>
inline bool vsl_quick_file_load(T &data1,
                                S &data2,
                                const vcl_string& path,
                                vcl_ostream* errorStream = &vcl_cerr)
{
  vsl_b_ifstream bfs(path);
  int reason = errno;
  if ( !(!bfs))
  {
    vsl_b_read(bfs,data1);
    vsl_b_read(bfs,data2);
    if (!(!bfs))
    {
      
      char dummy;
      vsl_b_read(bfs,dummy);
      if (bfs.is().eof())
      {
        bfs.close();
        if (errorStream)
          *errorStream << "Successfully loaded: " << path << '\n';
        return true;
      }
    }
  }
  reason = errno;
  bfs.close();
  if (errorStream)
    *errorStream << "Unable to load: "<< path <<'\n';
  return false;
}


template <class T, class S>
inline bool vsl_quick_file_save(const T &data1,
                                const S &data2,
                                const vcl_string& path,
                                vcl_ostream* errorStream = &vcl_cerr)
{
  vsl_b_ofstream bfs(path);
  if (!(!bfs))
  {
    vsl_b_write(bfs,data1);
    vsl_b_write(bfs,data2);
    if (!(!bfs))
    {
      bfs.close();
      if (errorStream)
        *errorStream << "Successfully saved: "<< path <<'\n';
      return true;
    }
  }
  bfs.close();
  if (errorStream)
    *errorStream << "Unable to save: " << path << '\n';
  return false;
}


template <class T, class S, class U>
inline bool vsl_quick_file_load(T &data1,
                                S &data2, U &data3,
                                const vcl_string& path,
                                vcl_ostream* errorStream = &vcl_cerr)
{
  vsl_b_ifstream bfs(path);
  if ( !(!bfs))
  {
    vsl_b_read(bfs,data1);
    vsl_b_read(bfs,data2);
    vsl_b_read(bfs,data3);
    if (!(!bfs))
    {
      
      char dummy;
      vsl_b_read(bfs,dummy);
      if (bfs.is().eof())
      {
        bfs.close();
        if (errorStream)
          *errorStream << "Successfully loaded: " << path << '\n';
        return true;
      }
    }
  }
  bfs.close();
  if (errorStream)
    *errorStream << "Unable to load: "<< path <<'\n';
  return false;
}


template <class T, class S, class U>
inline bool vsl_quick_file_save(const T &data1,
                                const S &data2, const U &data3,
                                const vcl_string& path,
                                vcl_ostream* errorStream = &vcl_cerr)
{
  vsl_b_ofstream bfs(path);
  if (!(!bfs))
  {
    vsl_b_write(bfs,data1);
    vsl_b_write(bfs,data2);
    vsl_b_write(bfs,data3);
    if (!(!bfs))
    {
      bfs.close();
      if (errorStream)
        *errorStream << "Successfully saved: "<< path <<'\n';
      return true;
    }
  }
  bfs.close();
  if (errorStream)
    *errorStream << "Unable to save: " << path << '\n';
  return false;
}


template <class T, class S, class U, class V>
inline bool vsl_quick_file_load(T &data1,
                                S &data2, U &data3, V &data4,
                                const vcl_string& path,
                                vcl_ostream* errorStream = &vcl_cerr)
{
  vsl_b_ifstream bfs(path);
  if ( !(!bfs))
  {
    vsl_b_read(bfs,data1);
    vsl_b_read(bfs,data2);
    vsl_b_read(bfs,data3);
    vsl_b_read(bfs,data4);
    if (!(!bfs))
    {
      
      char dummy;
      vsl_b_read(bfs,dummy);
      if (bfs.is().eof())
      {
        bfs.close();
        if (errorStream)
          *errorStream << "Successfully loaded: " << path << '\n';
        return true;
      }
    }
  }
  bfs.close();
  if (errorStream)
    *errorStream << "Unable to load: "<< path <<'\n';
  return false;
}


template <class T, class S, class U, class V>
inline bool vsl_quick_file_save(const T &data1, const S &data2,
                                const U &data3, const V &data4,
                                const vcl_string& path,
                                vcl_ostream* errorStream = &vcl_cerr)
{
  vsl_b_ofstream bfs(path);
  if (!(!bfs))
  {
    vsl_b_write(bfs,data1);
    vsl_b_write(bfs,data2);
    vsl_b_write(bfs,data3);
    vsl_b_write(bfs,data4);
    if (!(!bfs))
    {
      bfs.close();
      if (errorStream)
        *errorStream << "Successfully saved: "<< path <<'\n';
      return true;
    }
  }
  bfs.close();
  if (errorStream)
    *errorStream << "Unable to save: " << path << '\n';
  return false;
}


template <class T, class S, class U, class V, class W>
inline bool vsl_quick_file_load(T &data1,
                                S &data2, U &data3, V &data4, W &data5,
                                const vcl_string& path,
                                vcl_ostream* errorStream = &vcl_cerr)
{
  vsl_b_ifstream bfs(path);
  if ( !(!bfs))
  {
    vsl_b_read(bfs,data1);
    vsl_b_read(bfs,data2);
    vsl_b_read(bfs,data3);
    vsl_b_read(bfs,data4);
    vsl_b_read(bfs,data5);
    if (!(!bfs))
    {
      
      char dummy;
      vsl_b_read(bfs,dummy);
      if (bfs.is().eof())
      {
        bfs.close();
        if (errorStream)
          *errorStream << "Successfully loaded: " << path << '\n';
        return true;
      }
    }
  }
  bfs.close();
  if (errorStream)
    *errorStream << "Unable to load: "<< path <<'\n';
  return false;
}


template <class T, class S, class U, class V, class W>
inline bool vsl_quick_file_save(const T &data1, const S &data2, const U &data3,
                                const V &data4, const W &data5,
                                const vcl_string& path,
                                vcl_ostream* errorStream = &vcl_cerr)
{
  vsl_b_ofstream bfs(path);
  if (!(!bfs))
  {
    vsl_b_write(bfs,data1);
    vsl_b_write(bfs,data2);
    vsl_b_write(bfs,data3);
    vsl_b_write(bfs,data4);
    vsl_b_write(bfs,data5);
    if (!(!bfs))
    {
      bfs.close();
      if (errorStream)
        *errorStream << "Successfully saved: "<< path <<'\n';
      return true;
    }
  }
  bfs.close();
  if (errorStream)
    *errorStream << "Unable to save: " << path << '\n';
  return false;
}



template <class T, class S, class U, class V, class W, class X>
inline bool vsl_quick_file_load(T &data1, S &data2, U &data3,
                                V &data4, W &data5, X &data6,
                                const vcl_string& path,
                                vcl_ostream* errorStream = &vcl_cerr)
{
  vsl_b_ifstream bfs(path);
  if ( !(!bfs))
  {
    vsl_b_read(bfs,data1);
    vsl_b_read(bfs,data2);
    vsl_b_read(bfs,data3);
    vsl_b_read(bfs,data4);
    vsl_b_read(bfs,data5);
    vsl_b_read(bfs,data6);
    if (!(!bfs))
    {
      
      char dummy;
      vsl_b_read(bfs,dummy);
      if (bfs.is().eof())
      {
        bfs.close();
        if (errorStream)
          *errorStream << "Successfully loaded: " << path << '\n';
        return true;
      }
    }
  }
  bfs.close();
  if (errorStream)
    *errorStream << "Unable to load: "<< path <<'\n';
  return false;
}


template <class T, class S, class U, class V, class W, class X>
inline bool vsl_quick_file_save(const T &data1, const S &data2, const U &data3,
                                const V &data4, const W &data5, const X &data6,
                                const vcl_string& path,
                                vcl_ostream* errorStream = &vcl_cerr)
{
  vsl_b_ofstream bfs(path);
  if (!(!bfs))
  {
    vsl_b_write(bfs,data1);
    vsl_b_write(bfs,data2);
    vsl_b_write(bfs,data3);
    vsl_b_write(bfs,data4);
    vsl_b_write(bfs,data5);
    vsl_b_write(bfs,data6);
    if (!(!bfs))
    {
      bfs.close();
      if (errorStream)
        *errorStream << "Successfully saved: "<< path <<'\n';
      return true;
    }
  }
  bfs.close();
  if (errorStream)
    *errorStream << "Unable to save: " << path << '\n';
  return false;
}
#endif 
