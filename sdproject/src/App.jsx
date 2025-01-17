import React, { useState } from "react";

const App = () => {
  const [ano, setAno] = useState("");
  const [eventos, setEventos] = useState([]);
  const [loading, setLoading] = useState(false);

  const buscarEventos = async () => {
    if (!ano.trim()) {
      alert("Digite um ano válido!");
      return;
    }

    setLoading(true);
    setEventos([]); // Limpa os eventos anteriores

    // URL para buscar eventos históricos brasileiros
    const url = `https://pt.wikipedia.org/w/api.php?action=query&format=json&origin=*&list=search&srsearch=${ano} Brasil`;

    try {
      const resposta = await fetch(url);
      if (!resposta.ok) {
        throw new Error("Erro ao buscar eventos.");
      }

      const data = await resposta.json();
      setEventos(data.query.search || []);
    } catch (erro) {
      alert(erro.message);
      setEventos([]);
    } finally {
      setLoading(false);
    }
  };

  return (
    <div className="container">
      <h2>Fatos Históricos do Brasil</h2>
      <input
        type="number"
        placeholder="Digite um ano (ex: 2000)"
        value={ano}
        onChange={(e) => setAno(e.target.value)}
      />
      <button onClick={buscarEventos}>Buscar</button>

      {loading && <p>🔄 Carregando eventos...</p>}

      {eventos.length > 0 ? (
        <ul>
          {eventos.map((evento, index) => (
            <li key={index}>
              <a
                href={`https://pt.wikipedia.org/wiki/${evento.title.replace(
                  / /g,
                  "_"
                )}`}
                target="_blank"
                rel="noopener noreferrer"
              >
                {evento.title}
              </a>
              <p dangerouslySetInnerHTML={{ __html: evento.snippet }}></p>
            </li>
          ))}
        </ul>
      ) : (
        !loading && <p>Nenhum evento brasileiro encontrado para esse ano.</p>
      )}
    </div>
  );
};

export default App;
