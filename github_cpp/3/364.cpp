/*
 * Copyright (C) 2014-2015 Vy Nguyen
 * Github https://github.com/vy-nguyen/tvntd
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
#include <cpptype/lru-cache.h>

const std::string *
LruTabIter::key()
{
    return nullptr;
}

LruObj::ptr
LruTabIter::value()
{
    return nullptr;
}

/**
 * key_u64
 * -------
 */
uint64_t
LruTabIter::key_u64()
{
    return 0;
}

LruTable::LruTable(int max_elm) :
    m_max_elm(max_elm), m_hit_cnt(0), m_miss_cnt(0),
    m_kick_cnt(0), m_hash(max_elm), m_hash_end(m_hash)
{
    pthread_mutexattr_t attr;

    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ADAPTIVE_NP);
    pthread_mutex_init(&m_lock, &attr);
}

LruTable::~LruTable()
{
    clear();
}

/**
 * insert_key64
 * ------------
 */
bool
LruTable::insert_key64(LruObj::ptr obj)
{
    bool ret = false;
    if (obj == nullptr) {
        return ret;
    }
    pthread_mutex_lock(&m_lock);
    auto ref = m_hash.lookup(obj->obj_key64());
    if (ref == nullptr) {
        ret = true;
        m_miss_cnt++;
        m_hash.insert_key64(obj);
        obj->m_lru.obj_add_back(obj, &m_lru.m_list);
    } else {
        m_hit_cnt++;
        ref_obj_nolock(object_cast<LruObj>(ref.get()));
    }
    while (m_hash.size() > m_max_elm) {
        auto old = m_lru.dl_rm_front();
        verify(old != nullptr);

        m_kick_cnt++;
        m_hash.remove_obj(old);
    }
    pthread_mutex_unlock(&m_lock);

    return true;
}

/**
 * insert_keystr
 * -------------
 */
bool
LruTable::insert_keystr(LruObj::ptr obj)
{
    bool ret = false;
    if (obj == nullptr) {
        return ret;
    }
    pthread_mutex_lock(&m_lock);
    auto ref = m_hash.lookup(obj->obj_keystr());
    if (ref == nullptr) {
        ret = true;
        m_miss_cnt++;
        m_hash.insert_keystr(obj);
        obj->m_lru.obj_add_back(obj, &m_lru.m_list);
    } else {
        m_hit_cnt++;
        ref_obj(object_cast<LruObj>(ref.get()));
    }
    while (m_hash.size() > m_max_elm) {
        auto old = m_lru.dl_rm_front();
        verify(old != nullptr);

        m_kick_cnt++;
        m_hash.remove_obj(old);
    }
    pthread_mutex_unlock(&m_lock);

    return ret;
}

/**
 * remove_obj
 * ----------
 */
bool
LruTable::remove_obj(LruObj::ptr obj)
{
    if (obj == nullptr) {
        return false;
    }
    pthread_mutex_lock(&m_lock);
    obj->m_lru.obj_rm();
    m_hash.remove_obj(obj);
    pthread_mutex_unlock(&m_lock);

    return true;
}

void
LruTable::clear()
{
    pthread_mutex_lock(&m_lock);
    while (!m_lru.dl_empty()) {
        auto obj = m_lru.dl_rm_front();
        m_hash.remove_obj(obj);
    }
    verify(m_hash.size() == 0);
    pthread_mutex_unlock(&m_lock);
}

/**
 * ref_obj
 * -------
 */
void
LruTable::ref_obj(LruObj::ptr obj)
{
    pthread_mutex_lock(&m_lock);
    obj->m_lru.obj_rm();
    obj->m_lru.obj_add_back(obj, &m_lru.m_list);
    pthread_mutex_unlock(&m_lock);
}

void
LruTable::ref_obj_nolock(LruObj::ptr obj)
{
    obj->m_lru.obj_rm();
    obj->m_lru.obj_add_back(obj, &m_lru.m_list);
}

/**
 * lookup
 * ------
 */
LruObj::ptr
LruTable::lookup(uint64_t key)
{
    pthread_mutex_lock(&m_lock);
    auto obj = m_hash.lookup(key);
    pthread_mutex_unlock(&m_lock);

    if (obj != nullptr) {
        m_hit_cnt++;
        return object_cast<LruObj>(obj.get());
    }
    m_miss_cnt++;
    obj = lookup_missed(key);
    if (obj != nullptr) {
        auto save = object_cast<LruObj>(obj.get());
        insert_key64(save);
        return save;
    }
    return nullptr;
}

LruObj::ptr
LruTable::lookup(const char *key)
{
    pthread_mutex_lock(&m_lock);
    auto obj = m_hash.lookup(key);
    pthread_mutex_unlock(&m_lock);

    if (obj != nullptr) {
        m_hit_cnt++;
        return object_cast<LruObj>(obj.get());
    }
    m_miss_cnt++;
    obj = lookup_missed(key);
    if (obj != nullptr) {
        auto save = object_cast<LruObj>(obj.get());
        insert_keystr(save);
        return save;
    }
    return nullptr;
}

LruObj::ptr
LruTable::lookup(const std::string &key)
{
    pthread_mutex_lock(&m_lock);
    auto obj = m_hash.lookup(reinterpret_cast<const char *>(&key));
    pthread_mutex_unlock(&m_lock);

    if (obj != nullptr) {
        m_hit_cnt++;
        return object_cast<LruObj>(obj.get());
    }
    m_miss_cnt++;
    obj = lookup_missed(key);
    if (obj != nullptr) {
        auto save = object_cast<LruObj>(obj.get());
        insert_keystr(save);
        return save;
    }
    return nullptr;
}

void
LruTable::lookup(uint64_t key, lru_u64_cb cb)
{
    pthread_mutex_lock(&m_lock);
    auto obj = m_hash.lookup(key);
    pthread_mutex_unlock(&m_lock);

    if (obj == nullptr) {
        m_hit_cnt++;
        lookup_missed(key, cb);
    } else {
        m_miss_cnt++;
        cb(this, object_cast<LruObj>(obj.get()), key);
    }
 }

void
LruTable::lookup(const char *key, lru_str_cb cb)
{
    pthread_mutex_lock(&m_lock);
    auto obj = m_hash.lookup(key);
    pthread_mutex_unlock(&m_lock);

    if (obj == nullptr) {
        m_hit_cnt++;
        lookup_missed(key, cb);
    } else {
        m_miss_cnt++;
        cb(this, object_cast<LruObj>(obj.get()), key);
    }
}

void
LruTable::lookup(const std::string &key, lru_str_cb cb)
{
    pthread_mutex_lock(&m_lock);
    auto obj = m_hash.lookup(reinterpret_cast<const char *>(&key));
    pthread_mutex_unlock(&m_lock);

    if (obj == nullptr) {
        m_hit_cnt++;
        lookup_missed(key, cb);
    } else {
        m_miss_cnt++;
        cb(this, object_cast<LruObj>(obj.get()), key);
    }
}

/**
 * dump_stat
 * ---------
 */
void
LruTable::dump_stat()
{
    printf("Hit count........ %d\n"
           "Miss count....... %d\n"
           "Kick count....... %d\n", m_hit_cnt, m_miss_cnt, m_kick_cnt);
}
