#ifndef MACROS_H
#define MACROS_H

#define AUTO_Q_PROPERTY_CONSTANT(Type, name) \
protected: \
    Q_PROPERTY(Type name READ name CONSTANT) \
public: \
    Type name() const \
    { \
        return m_##name; \
    } \
private: \
    Type m_##name; \
protected:

#define AUTO_Q_PROPERTY(Type, name) \
protected: \
    Q_PROPERTY (Type name READ name WRITE set_##name NOTIFY name##Changed) \
public: \
    Type name() const \
    { \
        return m_##name; \
    } \
public Q_SLOTS: \
    void set_##name(Type name) \
    { \
        if (m_##name == name) return; \
        m_##name = name; \
        emit name##Changed(m_##name); \
    } \
private: \
    Type m_##name; \
Q_SIGNALS: \
    void name##Changed(Type name); \
\
protected:

#endif // MACROS_H
