/*
 * parser.h
 *
 * Created: 29.3.2019 16:01:26
 */ 


#ifndef PARSER_HPP_
#define PARSER_HPP_


template <uint8_t start_byte, uint8_t buffer_size>
class Parser
{
public:
	enum state_t { Start, Length, Cmd, Data };
	enum error_t {	OK = 0,
					Unknown_state,
					Invalid_start_byte,
					Too_short_packet,
					Too_long_packet,
					Invalid_CRC };

	Parser()
		: m_state(Start),
		  m_r_len(0),
		  m_t_len(0),
		  m_r_idx(0),
		  m_r_cmd(0),
		  m_error(OK)
		{
			assert(buffer_size <= 253);
		}

	bool push_byte(uint8_t byte)
	{
		switch(m_state)
		{
		case Start:
			//format(debug, "start byte 0x%x2") % byte;
			if (byte == start_byte)
			{
				m_state = Length;
				//::send(debug, " pass\n");
			}
			else
			{
				m_error = Invalid_start_byte;
				//format(debug, "!!! Invalid start byte received [0x%x2]!!!\n") % byte;
			}
			break;

		case Length:
			//format(debug, "length %3\n") % byte;
			if (byte < 1)
			{
				m_error = Too_short_packet;
				//format(debug, "!!! Too short packet [%3]!!!\n") % byte;
				m_state = byte == 0 ? Start : Cmd;
				break;
			}
			if (byte > (buffer_size - 2)) // CMD + CRC
			{
				m_error = Too_long_packet;
				//format(debug, "!!! Too long packet [%3]!!!\n") % byte;
			}
			m_r_len = byte - 2;
			m_state = Cmd;
			break;

		case Cmd:
			//format(debug, "cmd 0x%x2\n") % byte;
			m_r_cmd = byte;
			m_r_idx = 0;
			m_state = m_r_len == 0 ? Start : Data;
			break;

		case Data:
			//format(debug, "data[%3] %3") % m_r_idx % byte;
			if (m_r_idx < buffer_size)
				m_r_buff[m_r_idx++] = byte;
			//format(debug, "\tidx %3 len %3\n") % m_r_idx % m_r_len;
			if (m_r_idx == m_r_len)
			{
				m_state = Start;
				m_r_idx = 0;
			}
			break;

		default:
			m_error = Unknown_state;
			//format(debug, "!!! Unknown state of receiver state machine [0x%x2]!!!\n") % uint8_t(m_state);
		}
		return false;
	}

	uint8_t cmd() const
	{
		return m_r_cmd;
	}

	uint8_t size() const
	{
		return m_r_len;
	}

	uint8_t length() const
	{
		return m_r_len - m_r_idx;
	}

	error_t error() const
	{
		return m_error;
	}

	void clear_error()
	{
		m_error = OK;
	}

	void clear_receiver()
	{
		m_state = Start;
	}

	void clear_transmitter()
	{
		m_t_len = 0;
	}

	template <typename T>
	T read(uint8_t index) const
	{
		return *reinterpret_cast<const T*>(m_r_buff + index);
	}

	template <typename T>
	T read()
	{
		T v = read<T>(m_r_idx);
		m_r_idx += sizeof(T);
		if (m_r_idx > m_r_len)
			m_r_idx = 0;
		return v;
	}

	bool write(uint8_t byte)
	{
		if (m_t_len >= buffer_size)
			return false;
		m_t_buff[m_t_len++] = byte;
		return true;
	}

	template <typename T>
	bool write(const T& v)
	{
		if(m_t_len >= buffer_size)
			return false;
		uint8_t const* begin = reinterpret_cast<uint8_t const*>(&v);
		for(const uint8_t end = m_t_len + sizeof(v); m_t_len != end; ++m_t_len, ++begin)
		{
			m_t_buff[m_t_len] = *begin;
		}
		return true;
	}

	template <class Stream>
	void send(Stream& stream, uint8_t cmd)
	{
		stream.write(start_byte);
		stream.write(m_t_len + 1);
		stream.write(cmd);
		for (uint8_t i = 0; i != m_t_len; ++i)
			stream.write(m_t_buff[i]);
		clear_transmitter();
	}

	template <class Stream, typename T, typename... Args>
	void send(Stream& stream, uint8_t cmd, const T& value, Args... args)
	{
		write(value);
		send(stream, cmd, args...);
	}

private:
	state_t m_state;
	uint8_t m_r_len;
	uint8_t m_t_len;
	uint8_t m_r_idx;
	uint8_t m_r_cmd;
	uint8_t m_r_buff[buffer_size];
	uint8_t m_t_buff[buffer_size];
	error_t m_error;
};


#endif /* PARSER_HPP_ */